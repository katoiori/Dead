/*
================================================================================
					 IuWFNgwüQ[vO~O
	     Copyright (c) 2011 Human Academy Sendai. All rights reserved.
================================================================================

 yÎÛnrz
     Microsoft Windows 7È~

 yRpCz
     Microsoft VisualC++ 2013

 yvOz
	 Live2D.hpp
				Live2DNXwb_[t@C

 yo[Wz
	 * Version    2015.10.00      2015/08/28  03:10:03

================================================================================
*/

/*
//------------------------------------------------------------------------------
//	p[^[IDê
//------------------------------------------------------------------------------
"PARAM_ANGLE_X"			// px X
"PARAM_ANGLE_Y"			// px Y
"PARAM_ANGLE_Z"			// px Z
"PARAM_EYE_L_OPEN"		// ¶á JÂ
"PARAM_EYE_L_SMILE"		// ¶á Îç
"PARAM_EYE_R_OPEN"		// Eá JÂ
"PARAM_EYE_R_SMILE"		// Eá Îç
"PARAM_EYE_FORM"		// á Ï`
"PARAM_EYE_BALL_X"		// ÚÊ X
"PARAM_EYE_BALL_Y"		// ÚÊ Y
"PARAM_EYE_BALL_FORM"	// ÚÊ ûk
"PARAM_BROW_L_Y"		// ¶û ãº
"PARAM_BROW_R_Y"		// Eû ãº
"PARAM_BROW_L_X"		// ¶û ¶E
"PARAM_BROW_R_X"		// Eû ¶E
"PARAM_BROW_L_ANGLE"	// ¶û px
"PARAM_BROW_R_ANGLE"	// Eû px
"PARAM_BROW_L_FORM"		// ¶û Ï`
"PARAM_BROW_R_FORM"		// Eû Ï`
"PARAM_MOUTH_FORM"		// û Ï`
"PARAM_MOUTH_OPEN_Y"	// û JÂ
"PARAM_CHEEK"			// Æê
"PARAM_BODY_ANGLE_X"	// ÌÌñ] X
"PARAM_BODY_ANGLE_Y"	// ÌÌñ] X
"PARAM_BODY_ANGLE_Z"	// ÌÌñ] Z
"PARAM_BREATH"			// Äz
"PARAM_ARM_L_A"			// ¶r A
"PARAM_ARM_R_A"			// Er A
"PARAM_ARM_L_A"			// ¶r B
"PARAM_ARM_R_A"			// Er B 
"PARAM_BUST_Y"			// ¹ hê   
"PARAM_HAIR_FRONT"		// ¯hê O
"PARAM_HAIR_BACK"		// ¯hê ã
*/

#ifndef _INC_LIVE2D
#define _INC_LIVE2D

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

//------------------------------------------------------------------------------
//	é¾
//------------------------------------------------------------------------------
#define L2D_TARGET_D3D

//------------------------------------------------------------------------------
//	CN[ht@C
//------------------------------------------------------------------------------
#include <Live2D.h>
#include <Live2DModelD3D.h>
#include <..\..\DirectX\Include\d3dx9.h>

#include <list>
#include <set>
#include <vector>

//------------------------------------------------------------------------------
//	LIVE2DFILE\¢Ìè`
//------------------------------------------------------------------------------
struct Live2DFile {
	char*                                    ModelFileName;
	std::vector< std::basic_string<char> >   TextureFileName;
};

//------------------------------------------------------------------------------
//	LIVE2DMODEL\¢Ìè`
//------------------------------------------------------------------------------
struct Live2DModel {
friend class CLive2D;

private:
	live2d::Live2DModelD3D*           pModel;
	std::vector<IDirect3DTexture9*>   pTexture;

	template <class T>
	inline void SafeRelease(T& x)
	{
		if(x != NULL) {
			x->Release();
			x = NULL;
		}
	}

public:
	D3DXVECTOR3   position;
	D3DXVECTOR3   scale;
	float         rotationZ;

	float         width;
	float         height;

	Live2DModel()
	{
		pModel     = NULL;

		position.x = 0.0f;
		position.y = 0.0f;
		position.z = 0.0f;

		scale   .x = 1.0f;
		scale   .y = 1.0f;
		scale   .z = 1.0f;

		rotationZ  = 0.0f;
	}

	virtual ~Live2DModel()
	{
		const UINT   ARRAY_SIZE = pTexture.size();
		for(UINT i = 0; i < ARRAY_SIZE; i++) {
			if(pTexture[i] != NULL)
				pTexture[i]->Release();
		}

		delete pModel;
	}

	inline void SetScale(const float inScale)
	{
		scale.x = inScale;
		scale.y = inScale;
		scale.z = 1.0f;
	}

//	Live2DModel& operator=(live2d::Live2DModelD3D* pModel)
//	{
//		this->pModel = pModel;
//
//		width  = pModel->getModelImpl()->getCanvasWidth ();
//		height = pModel->getModelImpl()->getCanvasHeight();
//
//		return *this;
//	}

	inline operator live2d::Live2DModelD3D*  () const { return pModel; }
//	inline Live2DModel&            operator* ()       { return *this;  }
	inline live2d::Live2DModelD3D* operator->()       { return pModel; }
};

//------------------------------------------------------------------------------
//	Live2DNXè`
//------------------------------------------------------------------------------
class CLive2D {
public:
	virtual ~CLive2D();

	// VOgCX^XÌæ¾
	static CLive2D& GetInstance()
	{
		static CLive2D   theLive2D;
		return theLive2D;
	}

	// ú»Eðú
	bool Initialize(IDirect3DDevice9* pDevice);
	inline bool Attach(IDirect3DDevice9* pDevice) { return Initialize(pDevice); }

	void Release();

	// f¶¬Eðú
	Live2DModel* CreateModelFromFile(const Live2DFile& inFile);

	void ReleaseModel(Live2DModel*& inLive2DModel);
	void ReleaseAllModels();

	// `æ
	void Begin();
	void End();

	void Draw(Live2DModel& inLive2DModel);
	inline void Draw(Live2DModel* pLive2DModel) { Draw(*pLive2DModel); }

	// veNgÝè
	void SetResourceProtect(void* pResource, const bool inProtect);

private:
	CLive2D();

	template <class T>
	inline void SafeRelease(T& x)
	{
		if(x != NULL) {
			x->Release();
			x = NULL;
		}
	}

	CLive2D(const CLive2D&) = delete;
	CLive2D& operator=(const CLive2D&) = delete;

private:
	IDirect3DDevice9*         m_pDevice;
	std::list<Live2DModel*>   m_ModelList;

	D3DXMATRIXA16             m_View;
	D3DXMATRIXA16             m_Projection;

	std::set<void*>           m_ProtectedResource;
};

//------------------------------------------------------------------------------
//	}Nè`
//------------------------------------------------------------------------------
inline CLive2D& LIVE2D() { return CLive2D::GetInstance(); }

#endif /* _INC_LIVE2D */