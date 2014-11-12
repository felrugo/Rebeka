#include "RebFFMpeg.h"

RebDecoder::RebDecoder()
{
	container = 0;
	stream_id = -1;



	
	
}

void die(const char * p)
{
	printf(p);
}

void RebDecoder::SetSource(std::string file)
{

	 container = 0;

	 if (avformat_open_input(&container, file.c_str(), NULL, NULL) < 0) {
        die("Could not open file");
    }

    if (avformat_find_stream_info(container, NULL) < 0) {
        die("Could not find file info");
    }

    stream_id = -1;

    // To find the first audio stream. This process may not be necessary
    // if you can gurarantee that the container contains only the desired
    // audio stream
    int i;
    for (i = 0; i < container->nb_streams; i++) {
        if (container->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO) {
            stream_id = i;
            break;
        }
    }

    if (stream_id == -1) {
        die("Could not find an audio stream");
    }

    // Find the apropriate codec and open it
    codec_context = container->streams[stream_id]->codec;
    codec = avcodec_find_decoder(codec_context->codec_id);

    if (!avcodec_open2(codec_context, codec, NULL) < 0) {
        die("Could not find open the needed codec");
    }



	swrContext = swr_alloc_set_opts(NULL, 
		codec_context->channel_layout, AV_SAMPLE_FMT_S16, codec_context->sample_rate,
            codec_context->channel_layout, codec_context->sample_fmt, codec_context->sample_rate, 
            0, NULL);
int result = swr_init(swrContext);

// Create destination sample buffer
destBuffer = NULL;

av_samples_alloc_array_and_samples( &destBuffer,
                                    &destBufferLinesize,
                                    codec_context->channels,
                                    2048,
                                    AV_SAMPLE_FMT_S16,
                                    0);



}







int endWithError(char* msg, int error=0)
{
    //Display error message in console
    std::cout << msg << "\n";
    system("PAUSE");
    return error;
}

void RebDecoder::Load_Wave_File(char *fname, unsigned int buff)
{
   FILE *fp = NULL;                                                            //Create FILE pointer for the WAVE file
    fp=fopen(fname,"rb");                                            //Open the WAVE file
    if (!fp) return;                        //Could not open file
    
    //Variables to store info about the WAVE file (all of them is not needed for OpenAL)
    char type[4];
    DWORD size,chunkSize;
    short formatType,channels;
    DWORD sampleRate,avgBytesPerSec;
    short bytesPerSample,bitsPerSample;
    DWORD dataSize;
    
    //Check that the WAVE file is OK
    fread(type,sizeof(char),4,fp);                                              //Reads the first bytes in the file
    if(type[0]!='R' || type[1]!='I' || type[2]!='F' || type[3]!='F')            //Should be "RIFF"
    return;                                            //Not RIFF

    fread(&size, sizeof(DWORD),1,fp);                                           //Continue to read the file
    fread(type, sizeof(char),4,fp);                                             //Continue to read the file
    if (type[0]!='W' || type[1]!='A' || type[2]!='V' || type[3]!='E')           //This part should be "WAVE"
    return;                                           //Not WAVE
    
    fread(type,sizeof(char),4,fp);                                              //Continue to read the file
    if (type[0]!='f' || type[1]!='m' || type[2]!='t' || type[3]!=' ')           //This part should be "fmt "
    return;                                            //Not fmt 
    
    //Now we know that the file is a acceptable WAVE file
    //Info about the WAVE data is now read and stored
    fread(&chunkSize,sizeof(DWORD),1,fp);
    fread(&formatType,sizeof(short),1,fp);
    fread(&channels,sizeof(short),1,fp);
    fread(&sampleRate,sizeof(DWORD),1,fp);
    fread(&avgBytesPerSec,sizeof(DWORD),1,fp);
    fread(&bytesPerSample,sizeof(short),1,fp);
    fread(&bitsPerSample,sizeof(short),1,fp);
    
    fread(type,sizeof(char),4,fp);
    if (type[0]!='d' || type[1]!='a' || type[2]!='t' || type[3]!='a')           //This part should be "data"
    return;                                      //not data
    
    fread(&dataSize,sizeof(DWORD),1,fp);                                        //The size of the sound data is read
    
    //Display the info about the WAVE file
    /*cout << "Chunk Size: " << chunkSize << "\n";
    cout << "Format Type: " << formatType << "\n";
    cout << "Channels: " << channels << "\n";
    cout << "Sample Rate: " << sampleRate << "\n";
    cout << "Average Bytes Per Second: " << avgBytesPerSec << "\n";
    cout << "Bytes Per Sample: " << bytesPerSample << "\n";
    cout << "Bits Per Sample: " << bitsPerSample << "\n";
    cout << "Data Size: " << dataSize << "\n";*/
        
    unsigned char* buf= new unsigned char[dataSize];                            //Allocate memory for the sound data
    fread(buf,sizeof(BYTE),dataSize,fp);        //Read the sound data and display the 
	alBufferData(buff, AL_FORMAT_MONO16, buf, dataSize, sampleRate);                                                                            //number of bytes loaded.
     delete[] buf;                                                                          //Should be the same as the Data Size if OK
}


void RebDecoder::decode(unsigned int buff, ALuint frequency, ALenum format)
{
	// libav
    //buff size is 2048



    AVFrame* decodedFrame;
	decodedFrame=av_frame_alloc();
    int len;

	/*while(1)
	{*/


decerr:

	if (av_read_frame(container, &packet) < 0) {
           die("end of stream");
        }

	if(packet.stream_index!=stream_id) {
			// Skip Video and subtitle packets
            printf("V");
        }
        printf("A");
        // Decodes audio data from `packet` into the frame

		       while( packet.size >0) {
            int finishedFrame=0;
            len = avcodec_decode_audio4(codec_context, decodedFrame, &finishedFrame, &packet);

            if(len<0) {
                printf("error");
                goto decerr;
            }

            if (finishedFrame) {
			   // Decoded data is now available in
			   // decodedFrame->data[0]
			   
               int data_size = av_samples_get_buffer_size(NULL, codec_context->channels,
                                                       decodedFrame->nb_samples,
                                                       codec_context->sample_fmt, 1);

			   int outputSamples = swr_convert(swrContext, 
				   destBuffer, destBufferLinesize, 
                                        (const uint8_t**)decodedFrame->extended_data, decodedFrame->nb_samples);

			   int bufferSize = av_get_bytes_per_sample(AV_SAMPLE_FMT_S16) * codec_context->channels
                            * outputSamples;

        int64_t duration = decodedFrame->pkt_duration;
        int64_t dts = decodedFrame->pkt_dts;


               // OpenAL consumes buffers in the background
               // we first need to initialize the OpenAL buffers then
               // start continous playback.

			   /*if(buffsize + data_size > 2048)
			   {
				   buffdataplus = malloc(buffsize + data_size);
				   buffdataplus = 
			   }

			   buffdata = decodedFrame->data[0];
			   buffsize += data_size;*/
			  
			   
		alBufferData(buff, AL_FORMAT_STEREO16, destBuffer[0], bufferSize, decodedFrame->sample_rate);
                   if(alGetError() != AL_NO_ERROR) {
                       fprintf(stderr, "Error loading :(\n");
            }
				  /* delete[] destBuffer;*/
			}

            //There may be more than one frame of audio data
            //inside the packet.
            packet.size-=len;
            packet.data+=len;
        } // while packet.size > 0
			   av_free_packet(&packet);
			   av_frame_free(&decodedFrame);

	/*}*/
}


	RebDecoder::~RebDecoder()
	{
	avformat_close_input(&container);
	}