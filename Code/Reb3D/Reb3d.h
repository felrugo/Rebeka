/*******************************************************************
 * RebEngine!                                                      *
 * (c)2002 by Stefan Zerbst | www.Reb.info                         *
 *-----------------------------------------------------------------*
 * File: Reb3d.h                                                   *
 * part of static math lib implementing basic 3D math objects      *
 *******************************************************************/

// this is the main include file for the Reb3d.lib

#ifndef _Reb3D_H_
#define _Reb3D_H_



// I N C L U D E S /////////////////////////////////////////////////

#include <math.h>
#include <stdio.h>
#include <memory.h>     // memset



const double RebPI  =  3.14159265;
const double RebPI2 =  1.5707963;
const double Reb2PI =  6.2831853;
const float  RebG   = -32.174f; // ft/s^2
const float PI = 3.14159265f;
const float  RebEPSILON = 0.00001f;

// D E F I N E S ///////////////////////////////////////////////////

#ifndef NULL
#define NULL 0
#endif

#define RebFRONT    0
#define RebBACK     1
#define RebPLANAR   2
#define RebCLIPPED  3
#define RebCULLED   4
#define RebVISIBLE  5

// M A C R O S /////////////////////////////////////////////////////

float _fabs(float f);

bool Reb3DInitCPU(void);


// S T R U C T S ///////////////////////////////////////////////////

typedef struct CPUINFO_TYP {
   bool bSSE;        // Streaming SIMD Extensions
   bool bSSE2;		 // STreaming SIMD Extensions 2
   bool bSSE4;		 // Streaming SIMD Extensions 4
   bool b3DNOW;      // 3DNow! (vendor independant)
   bool b3DNOWEX;    // 3DNow! (AMD specific extensions)
   bool bMMX;        // MMX support
   bool bMMXEX;      // MMX (AMD specific extensions)
   bool bEXT;        // extended features available
   char vendor[13];  // vendor name
   char name[48];    // cpu name
   } CPUINFO;



// F O R W A R D   D E C L A R A T I O N S /////////////////////////

class RebMatrix;
class RebGLTrans;
class RebObb;
class RebAabb;
class RebPlane;
class RebQuat;
class RebPolygon;


// C L A S S E S ///////////////////////////////////////////////////

// Our basic 4D vector class
class __declspec(dllexport) RebVector {
   public:
      float x, y, z, w;       // coordinateset

      //---------------------------------------

      RebVector(void) { x=0, y=0, z=0, w=1.0f; }
      RebVector(float _x, float _y, float _z)
         { x=_x; y=_y; z=_z; w=1.0f; }

      inline void  Set(float _x, float _y, float _z, float _w=1.0f);
      inline float GetLength(void);                   // length
      inline float GetSqrLength(void) const;          // square length
      inline void  Negate(void);                      // vector mult -1
      inline void  Normalize(void);                   // normalize
      inline float AngleWith( RebVector &v);          // angle in rad
      inline void  RotateWith(const RebMatrix&);      // apply rotation part
      inline void  InvRotateWith(const RebMatrix&);   // apply inverse rotation
      inline void  Difference(const RebVector &v1,    // from v1 to v2
                              const RebVector &v2);
      void operator += (const RebVector &v);          // operator +=
      void operator -= (const RebVector &v);          // operator -=
      void operator *= (float f);                     // scale vector
      void operator /= (float f);                     // scale down
      void operator += (float f);                     // add scalar
      void operator -= (float f);                     // subtract scalar
      float     operator * (const RebVector &v)const; // dot product
      RebVector operator * (float f)const;            // scale vector
      RebVector operator / (float f)const;            // scalar divide
      RebVector operator + (float f)const;            // add scalar
      RebVector operator - (float f)const;            // scale down
      RebQuat   operator * (const RebQuat   &q)const; // vector * quaternion
      RebVector operator * (const RebMatrix &m)const; // vector-matrix product
      RebVector operator + (const RebVector &v)const; // addition
      RebVector operator - (const RebVector &v)const; // subtraction

      inline void Cross(const RebVector &v1,          // cross product
                        const RebVector &v2); 
   };  // class
/*----------------------------------------------------------------*/


// Our basic matrix class
class __declspec(dllexport) RebMatrix {
   public:
      float _11, _12, _13, _14;
      float _21, _22, _23, _24;
      float _31, _32, _33, _34;
      float _41, _42, _43, _44;
	  RebVector pos;
	  RebVector ori;
      //---------------------------------------

      RebMatrix(void) { /* nothing to do */ ; }

      inline void Identity(void);                       // identity matrix
      inline void RotaX(float a);                       // x axis
      inline void RotaY(float a);                       // y axis
      inline void RotaZ(float a);                       // z axis
      inline void Rota(const RebVector &vc);            // x, y and z
      inline void Rota(float x, float y, float z);      // x, y and z
	  inline void RotyByDeg(float x, float y, float z);
      inline void RotaArbi(const RebVector &vcAxis, float a);
      inline void ApplyInverseRota(RebVector *pvc);
      inline void Translate(float dx, float dy, float dz);
      inline void SetTranslation(RebVector vc, bool EraseContent=false);
	   inline RebVector GetTranslation(void);
	   inline RebVector GetRotation(void);

      inline void Billboard(RebVector vcPos, RebVector vcDir,
                            RebVector vcWorldUp = RebVector(0,1,0));
      inline void LookAt(RebVector vcPos, RebVector vcLookAt, 
                         RebVector vcWorldUp = RebVector(0,1,0));

      inline void TransposeOf(const RebMatrix &m);       // transpose m, save result in this
      inline void InverseOf(const RebMatrix &m);         // invert m, save result in this
      
      RebMatrix operator * (const RebMatrix &m)const;    // matrix multiplication
      RebVector operator * (const RebVector &vc)const;   // matrix vector multiplication
   }; // class
/*----------------------------------------------------------------*/


// Our OpenGL based transformation data

class _declspec(dllexport) RebGLTrans
{
public:

	RebVector pos;
	RebVector ori;

	RebGLTrans();
	RebGLTrans(RebVector spos, RebVector sori);
	inline void Identity(void);
	RebGLTrans operator + (const RebGLTrans &m)const;
	RebGLTrans operator * (const RebGLTrans &m)const;


};


// Our basic ray class
class __declspec(dllexport) RebRay {
   public:
      RebVector m_vcOrig,  // ray origin
                m_vcDir;   // ray direction

      //---------------------------------------

      RebRay(void) { /* nothing to do */ ; }

      inline void Set(RebVector vcOrig, RebVector vcDir);
      inline void DeTransform(const RebMatrix &_m); // move to matrixspace

      bool Intersects(const RebVector &vc0, const RebVector &vc1,
                      const RebVector &vc2, bool bCull,
                      float *t);
      bool Intersects(const RebVector &vc0, const RebVector &vc1,
                      const RebVector &vc2, bool bCull,
                      float fL, float *t);
      bool Intersects(const RebPlane &plane, bool bCull,
                      float *t, RebVector *vcHit);       
      bool Intersects(const RebPlane &plane, bool bCull,
                      float fL, float *t, RebVector *vcHit);
      bool Intersects(const RebAabb &aabb, float *t);
      bool Intersects(const RebAabb &aabb, float fL, float *t);
      bool Intersects(const RebObb &obb, float *t);
      bool Intersects(const RebObb &obb, float fL, float *t);
   }; // class
/*----------------------------------------------------------------*/


// Our basic plane class
class __declspec(dllexport) RebPlane {
   public:
      RebVector m_vcN,       // plane normal vector
                m_vcPoint;   // point on plane
      float     m_fD;        // distance to origin

      //---------------------------------------

      RebPlane(void) { /* nothing to do */ ; }

      inline void  Set(const RebVector &vcN, const RebVector &vcP);
      inline void  Set(const RebVector &vcN, const RebVector &vcP, float fD);
      inline void  Set(const RebVector &v0,  const RebVector &v1, const RebVector &v2);
      inline float Distance(const RebVector &vcPoint);
      inline int   Classify(const RebVector &vcPoint);
             int   Classify(const RebPolygon &Polygon);

      bool Clip(const RebRay*, float, RebRay*, RebRay*);

      bool Intersects(const RebVector &vc0, const RebVector &vc1, 
                      const RebVector &vc2);
      bool Intersects(const RebPlane &plane, RebRay *pIntersection);
      bool Intersects(const RebAabb &aabb);
      bool Intersects(const RebObb &obb);

   }; // class
/*----------------------------------------------------------------*/


// Our basic orientedbox class
class __declspec(dllexport) RebObb {
   public:
      float     fA0,   fA1,  fA2; // half axis length
      RebVector vcA0, vcA1, vcA2; // box axis
      RebVector vcCenter;         // centerpoint

      //---------------------------------------

      RebObb(void) { /* nothing to do */ ; }

      inline void DeTransform(const RebObb &obb, 
                              const RebMatrix &m);

      bool Intersects(const RebRay &Ray, float *t);
      bool Intersects(const RebRay &Ray, float fL, float *t);
      bool Intersects(const RebObb &Obb);
      bool Intersects(const RebVector &v0, 
                      const RebVector &v1,
                      const RebVector &v2);

      int  Cull(const RebPlane *pPlanes, int nNumPlanes);      

   private:
      void ObbProj(const RebObb &Obb, const RebVector &vcV, 
                   float *pfMin, float *pfMax);
      void TriProj(const RebVector &v0, const RebVector &v1, 
                   const RebVector &v2, const RebVector &vcV, 
                   float *pfMin, float *pfMax);
   }; // class
/*----------------------------------------------------------------*/

// Our basic axisalignedbox class
class __declspec(dllexport) RebAabb {
   public:
      RebVector vcMin, vcMax; // box extreme points
      RebVector vcCenter;     // centerpoint

      //---------------------------------------

      RebAabb(void) { /* nothing to do */ ; }
      RebAabb(RebVector vcMin, RebVector vcMax);

      void Construct(const RebObb *pObb);                  // build from obb
      int  Cull(const RebPlane *pPlanes, int nNumPlanes);  

      // normals pointing outwards
      void GetPlanes(RebPlane *pPlanes);

      bool Contains(const RebRay &Ray, float fL);
      bool Intersects(const RebRay &Ray, float *t);
      bool Intersects(const RebRay &Ray, float fL, float *t);
      bool Intersects(const RebAabb &aabb);
      bool Intersects(const RebVector &vc0);
   }; // class
/*----------------------------------------------------------------*/


// Our basic polygon class
class __declspec(dllexport) RebPolygon {
   friend class RebPlane;        // access for easier classifying

   private:
      RebPlane       m_Plane;    // plane which poly lies in

      int            m_NumP;     // number of points
      int            m_NumI;     // number of indices
      RebAabb        m_Aabb;     // bounding box
      unsigned int   m_Flag;     // whatever you want it to be

      void CalcBoundingBox(void);

   //---------------------------------------

   public:
      RebPolygon(void);
      ~RebPolygon(void);


      RebVector    *m_pPoints;  // list of points
      unsigned int *m_pIndis;   // index list

      void          Set(const RebVector *pPoints, int nNumP,
                        const unsigned int *pIndis, int nNumI);

      void          Clip(const RebPlane &Plane, 
                         RebPolygon *pFront,
                         RebPolygon *pBack);
      void          Clip(const RebAabb &aabb);
      int           Cull(const RebAabb &aabb);

      void          CopyOf( const RebPolygon &Poly );

      void          SwapFaces(void);

      bool          Intersects(const RebRay &Ray, bool, float *t);
      bool          Intersects(const RebRay &Ray, bool, float fL, float *t);

      int           GetNumPoints(void)      { return m_NumP;    }
      int           GetNumIndis(void)       { return m_NumI;    }
      RebVector*    GetPoints(void)         { return m_pPoints; }
      unsigned int* GetIndices(void)        { return m_pIndis;  }
      RebPlane      GetPlane(void)          { return m_Plane;   }
      RebAabb       GetAabb(void)           { return m_Aabb;    }
      unsigned int  GetFlag(void)           { return m_Flag;    }
      void          SetFlag(unsigned int n) { m_Flag = n;       }

      // DEBUG ONLY
      void Print(FILE*);
   }; // class
/*----------------------------------------------------------------*/


// Our basic quaternion class
class __declspec(dllexport) RebQuat {
   public:
      float x, y, z, w;

      //---------------------------------------

      RebQuat(void) { x=0.0f, y=0.0f, z=0.0f, w=1.0f; }
      RebQuat(float _x, float _y, float _z, float _w)
         { x=_x; y=_y; z=_z; w=_w; }

      void  MakeFromEuler(float fPitch, float fYaw, float fRoll);
      void  Normalize();
      void  Conjugate(RebQuat q);
      void  GetEulers(float *fPitch, float *fYaw, float *fRoll);
      void  GetMatrix(RebMatrix *m);
      float GetMagnitude(void);


      void    operator /= (float f);
      RebQuat operator /  (float f);

      void    operator *= (float f);
      RebQuat operator *  (float f);

      RebQuat operator *  (const RebVector &v) const;

      RebQuat operator *  (const RebQuat &q) const;
      void    operator *= (const RebQuat &q);

      void    operator += (const RebQuat &q);
      RebQuat operator +  (const RebQuat &q) const;

      RebQuat operator~(void) const { return RebQuat(-x, -y, -z, w); }

      void Rotate(const RebQuat &q1, const RebQuat &q2);

      RebVector Rotate(const RebVector &v);

   }; // class
/*----------------------------------------------------------------*/



#endif // header name define

