/******************************************************************************
 *
 * LifeLike - LifeLike computer interfaces
 * Copyright (C) 2007 Sangyoon Lee, Electronic Visualization Laboratory, 
 * University of Illinois at Chicago
 *
 * This software is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either Version 2.1 of the License, or 
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public 
 * License for more details.
 * 
 * You should have received a copy of the GNU Lesser Public License along
 * with this software; if not, write to the Free Software Foundation, Inc., 
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * Questions or comments about LifeLike should be directed to 
 * cavern@evl.uic.edu
 *
 *****************************************************************************/
/*
/*
-----------------------------------------------------------------------------
Filename:    BaseApplication.h
-----------------------------------------------------------------------------
This source file is generated by the Ogre AppWizard. Based on the Example 
Framework for OGRE (Object-oriented Graphics Rendering Engine)

Copyright (c) 2000-2007 The OGRE Team
For the latest info, see http://www.ogre3d.org/
-----------------------------------------------------------------------------
*/

#ifndef __BaseApplication_h_
#define __BaseApplication_h_

#include <Ogre.h>
#include <OgreStringConverter.h>
#include <OgreException.h>

//Use this define to signify OIS will be used as a DLL
//(so that dll import/export macros are in effect)
#define OIS_DYNAMIC_LIB
#include <OIS/OIS.h>

using namespace Ogre;

#include <CEGUI.h>
#include <CEGUISystem.h>
#include <CEGUISchemeManager.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>

#include <SdkTrays.h>

class BaseApplication : public Ogre::Singleton<BaseApplication>,  public FrameListener, public WindowEventListener, public OIS::KeyListener, public OIS::MouseListener, OgreBites::SdkTrayListener
{
public:
	BaseApplication(void);
	virtual ~BaseApplication(void);
	virtual void go(void);

protected:
	virtual bool setup();
	virtual bool configure(void);
	virtual void chooseSceneManager(void);
	virtual void createCamera(void);
	virtual void createFrameListener(void);
	virtual void createScene(void) = 0; // Override me!
	virtual void destroyScene(void);
	virtual void createViewports(void);
	virtual void setupResources(void);
	virtual void createResourceListener(void);
	virtual void loadResources(void);
	virtual bool processUnbufferedKeyInput(const FrameEvent& evt);
	virtual bool processUnbufferedMouseInput(const FrameEvent& evt);
	virtual void moveCamera();

	virtual bool frameStarted(const FrameEvent& evt);
	virtual bool frameEnded(const FrameEvent& evt);

    // Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	virtual void setupInput();
	virtual void createInputDevices();

	void showDebugOverlay(bool show);
	void switchMouseMode();
	void switchKeyMode();
	bool keyPressed( const OIS::KeyEvent &arg );
	bool keyReleased( const OIS::KeyEvent &arg );
	bool mouseMoved( const OIS::MouseEvent &arg );
	bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

	//Adjust mouse clipping area
	virtual void windowResized(RenderWindow* rw);
	//Unattach OIS before window shutdown (very important under Linux)
	virtual void windowClosed(RenderWindow* rw);

	void requestShutdown(void);
	virtual void setupEventHandlers(void);
	bool handleQuit(const CEGUI::EventArgs& e);

	Root *mRoot;
	Camera* mPrimaryCamera;
	Camera* mSecondaryCamera;
	SceneNode* m_pPrimaryCameraNode;

	SceneManager* mSceneMgr;
	RenderWindow* mWindow, *mWindow2;
	bool mShutdownRequested;
	int mSceneDetailIndex ;
	Real mMoveSpeed;
	Degree mRotateSpeed;
	Overlay* mDebugOverlay;
	Overlay* mPADOverlay;
	Ogre::String mResourcePath;

	//OIS Input devices
	OIS::InputManager* mInputManager;
	OIS::Mouse*    mMouse;
	OIS::Keyboard* mKeyboard;
	Vector3 mTranslateVector;
	bool mStatsOn;
	bool mUseBufferedInputKeys, mUseBufferedInputMouse, mInputTypeSwitchingOn;
	unsigned int mNumScreenShots;
	float mMoveScale;
	Degree mRotScale;
	Real mTimeUntilNextToggle; // just to stop toggles flipping too fast
	Radian mRotX, mRotY;

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	HWND windonHandle;
#endif

    // OgreBites
    OgreBites::SdkTrayManager* mTrayMgr;
    OgreBites::ParamsPanel* mDetailsPanel;     // sample details panel

};

#endif // #ifndef __BaseApplication_h_