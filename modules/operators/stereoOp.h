/*
 * Copyright (C) 2012 Hernan Badino <hernan.badino@gmail.com>
 *
 * This file is part of QCV
 *
 * QCV is under the terms of the GNU Lesser General Public License
 * version 2.1. See the GNU LGPL version 2.1 for details.
 * QCV is distributed "AS IS" without ANY WARRANTY, without even the
 * implied warranty of merchantability or fitness for a particular
 * purpose. 
 *
 * In no event shall the authors or contributors be liable
 * for any direct, indirect, incidental, special, exemplary, or
 * consequential damages arising in any way out of the use of this
 * software.
 *
 * By downloading, copying, installing or using the software you agree
 * to this license. Do not download, install, copy or use the
 * software, if you do not agree to this license.
 */

#ifndef __OPENCVSTEREOOP_H
#define __OPENCVSTEREOOP_H

/**
*******************************************************************************
*
* @file stereoOp.h
*
* \class CStereoOp
* \author Hernan Badino (hernan.badino@gmail.com)
* \brief Compute stereo using OpenCV stereo algorithms
*
*******************************************************************************/

/* INCLUDES */
#include <math.h>
#include <limits>

#include <cv.h>
#include <highgui.h>

#include "matVector.h"
#include "operator.h"
#include "colorEncoding.h"

/* PROTOTYPES */

/* CONSTANTS */

namespace QCV
{
    class CMyStereoSGBM: public cv::StereoSGBM
    {
    public:
        CMyStereoSGBM() : cv::StereoSGBM()
        {
        }

        ADD_PARAM_ACCESS (int,  numberOfDisparities, NumberOfDisparities );
        ADD_PARAM_ACCESS (int,  minDisparity,        MinDisparity );
        ADD_PARAM_ACCESS (int,  SADWindowSize,       SADWindowSize );
        ADD_PARAM_ACCESS (int,  preFilterCap,        PreFilterCap );
        ADD_PARAM_ACCESS (int,  uniquenessRatio,     UniquenessRatio );
        ADD_PARAM_ACCESS (int,  P1,                  P1 );
        ADD_PARAM_ACCESS (int,  P2,                  P2 );
        ADD_PARAM_ACCESS (int,  speckleWindowSize,   SpeckleWindowSize );        
        ADD_PARAM_ACCESS (int,  speckleRange,        SpeckleRange );
        ADD_PARAM_ACCESS (int,  disp12MaxDiff,       Disp12MaxDiff );
        ADD_PARAM_ACCESS (bool, fullDP,              FullDP );
    };

    class CMyStereoBM: public cv::StereoBM
    {
    public:
        CMyStereoBM() : cv::StereoBM()
        {
        }
        
        ADD_PARAM_ACCESS (int,  state->numberOfDisparities,  NumberOfDisparities );
        ADD_PARAM_ACCESS (int,  state->preFilterType,        PreFilterType );
        ADD_PARAM_ACCESS (int,  state->preFilterSize,        PreFilterSize );
        ADD_PARAM_ACCESS (int,  state->preFilterCap,         PreFilterCap );
        ADD_PARAM_ACCESS (int,  state->uniquenessRatio,      UniquenessRatio );
        ADD_PARAM_ACCESS (int,  state->SADWindowSize,        SADWindowSize );
        ADD_PARAM_ACCESS (int,  state->textureThreshold,     TextureThreshold );

        ADD_PARAM_ACCESS (int,  state->speckleWindowSize,    SpeckleWindowSize );
        ADD_PARAM_ACCESS (int,  state->speckleRange,         SpeckleRange );
        ADD_PARAM_ACCESS (int,  state->trySmallerWindows,    TrySmallerWindows );

        ADD_PARAM_ACCESS (int,  state->disp12MaxDiff,        Disp12MaxDiff );
    };

    typedef cv::Mat TOutputType;

    class CStereoOp: public COperator
    {
    /// Constructor, Desctructors
    public:    
        typedef enum {
            SA_SGBM,
            SA_BM
        } EStereoAlgorithm;            

    /// Parameter access
    public:    
        ADD_PARAM_ACCESS         (std::string,       m_leftImgId_str,   LeftImageId );
        ADD_PARAM_ACCESS         (std::string,       m_rightImgId_str,  RightImageId );
        ADD_PARAM_ACCESS         (std::string,       m_dispImgId_str,   DisparityImageId );

        ADD_PARAM_ACCESS         (EStereoAlgorithm,  m_alg_e,           StereoAlgorithm );
        ADD_PARAM_ACCESS_BOUNDED (int,               m_scale_i,         Downscale, 1, 6 );
        ADD_PARAM_ACCESS         (bool,              m_convert2Float_b, ConvertDispImg2Float );
        ADD_PARAM_ACCESS         (bool,              m_compute_b,       Compute );

        ADD_PARAM_ACCESS         (bool,              m_show3D_b,        Show3DMesh );

    /// Constructor, Desctructors
    public:    
        
        /// Constructors.
        CStereoOp ( COperator * const f_parent_p = NULL,
                    const std::string     f_name_str = "OpenCV Stereo" );
        
        /// Virtual destructor.
        virtual ~CStereoOp ();

        /// Cycle event.
        virtual bool cycle( );
    
        /// Show event.
        virtual bool show();
    
        /// Init event.
        virtual bool initialize();
    
        /// Reset event.
        virtual bool reset();
    
        /// Exit event.
        virtual bool exit();

        /// User Operation Events

    public:
        /// Key pressed in display.
        virtual void keyPressed ( CKeyEvent * f_event_p );

       
    /// I/O registration.
    public:
        /// Set the input of this operator
        bool setInput  ( const CMatVector & f_input );

    protected:

    protected:

        bool getInput();
        
        bool validateImages() const;

        void registerDrawingLists();

        void registerParameters();

        void show3D();
    private:

        /// Compute?
        bool                        m_compute_b;
        
        /// Left image id
        std::string                 m_leftImgId_str;

        /// Right image id
        std::string                 m_rightImgId_str;

        /// Disparity image id
        std::string                 m_dispImgId_str;
        
        /// Stereo algorithm to use
        EStereoAlgorithm            m_alg_e;
        
        ///  SGBM struct
        CMyStereoSGBM               m_sgbm;
        
        /// BM struct
        CMyStereoBM                 m_sbm;

        /// Left image
        cv::Mat                     m_leftImg;

        /// Right image
        cv::Mat                     m_rightImg;

        /// Output disparity image
        cv::Mat                     m_dispImg;

        /// Float output disparity image
        cv::Mat                     m_dispImgFloat;

        /// Disparity color encoding
        CColorEncoding              m_dispCE;

        /// Down-scale factor
        int                         m_scale_i;
        
        /// Convert disparity image to float?
        bool                        m_convert2Float_b;

        /// For 3D point mesh
        cv::Mat                     m_3DPointImg;

        /// Show 3D mesh?
        bool                        m_show3D_b;
        

    };
}
#endif // __OPENCVSTEREOOP_H
 
