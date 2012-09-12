/*
 * Copyright (C) 2012 Hernan Badino <hernan.badino@gmail.com>
 *
 * This file is part of QCV
 *
 * QCV is under the terms of the GNU General Public License, version 2.
 * See the GNU General Public License, version 2 for details.
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

#ifndef __COLORS_H
#define __COLORS_H

/*@@@**************************************************************************
 * \file  colors
 * \author Hernan Badino
 * \notes  
 *******************************************************************************
 *****             (C) Hernan Badino 2012 - All Rights Reserved            *****
 ******************************************************************************/

/* INCLUDES */
#include <algorithm>
#include <inttypes.h>

/* CONSTANTS */

namespace QCV
{
    struct SRgb;

    /// RGBA Color
    struct SRgba
    {
        SRgba() {};
        SRgba ( const int f_r_i, 
                const int f_g_i, 
                const int f_b_i, 
                const int f_a_i = 255 )
        {
            r = std::max(std::min(255, f_r_i), 0);
            g = std::max(std::min(255, f_g_i), 0);
            b = std::max(std::min(255, f_b_i), 0);
            a = std::max(std::min(255, f_a_i), 0);
        }
        
        SRgba ( const SRgb & other,
                uint8_t      f_a_8ui = 255 );

        SRgba ( uint8_t f_r_8ui, 
                uint8_t f_g_8ui, 
                uint8_t f_b_8ui, 
                uint8_t f_a_8ui = 255 )
                : r(f_r_8ui),
                  g(f_g_8ui),
                  b(f_b_8ui),
                  a(f_a_8ui)
        {
        }

        void set (  const int f_r_i, 
                    const int f_g_i, 
                    const int f_b_i, 
                    const int f_a_i = 255 )
        {
            r = std::max(std::min(255, f_r_i), 0);
            g = std::max(std::min(255, f_g_i), 0);
            b = std::max(std::min(255, f_b_i), 0);
            a = std::max(std::min(255, f_a_i), 0);
        }

        const SRgba& operator =  ( const SRgb & other );

        bool operator == ( const SRgba & other ) const
        {
            return r == other.r && g == other.g && b == other.b  && a == other.a;
        }

        bool operator != ( const SRgba & other ) const
        {
            return ! (operator == ( other ));
        }

        operator bool ( )
        {
            return r != 0 || g!=0 || b!=0 || a!=0;
        }

        union
        {
            struct 
            {    
                uint8_t  red;
                uint8_t  green;
                uint8_t  blue;
                uint8_t  alpha;
            };

            struct 
            {    
                uint8_t  r;
                uint8_t  g;
                uint8_t  b;
                uint8_t  a;
            };
            
            uint8_t celem[4];
        };
        
    } ;

    /// RGB Color
    struct SRgb 
    {
        SRgb() {};
        SRgb ( const int f_r_i, 
               const int f_g_i, 
               const int f_b_i )
        {
            r = std::max(std::min(255, f_r_i), 0);
            g = std::max(std::min(255, f_g_i), 0);
            b = std::max(std::min(255, f_b_i), 0);
        }

        SRgb ( uint8_t f_r_8ui,
               uint8_t f_g_8ui, 
               uint8_t f_b_8ui )
                : r(f_r_8ui),
                  g(f_g_8ui),
                  b(f_b_8ui)
        {
        }
        
        SRgb ( SRgba other )
        {
            r = other.r;
            g = other.g;
            b = other.b;
        }

        const SRgb& operator = ( const SRgba & other )
        {
            r = other.r;
            g = other.g;
            b = other.b;
            return (*this);
        }

        bool operator == ( const SRgb & other ) const
        {
            return r == other.r && g == other.g && b == other.b;
        }        

        bool operator != ( const SRgba & other ) const
        {
            return ! (operator == ( other ));
        }

        operator bool ( )
        {
            return r != 0 || g!=0 || b!=0;
        }
        
        void set (  const int f_r_i, 
                    const int f_g_i, 
                    const int f_b_i )
            
        {
            r = std::max(std::min(255, f_r_i), 0);
            g = std::max(std::min(255, f_g_i), 0);
            b = std::max(std::min(255, f_b_i), 0);
        }

        union
        {
            struct 
            {    
                uint8_t  red;
                uint8_t  green;
                uint8_t  blue;
            };

            struct 
            {    
                uint8_t  r;
                uint8_t  g;
                uint8_t  b;
            };
            
            uint8_t celem[3];
        };
    };

    inline SRgba::SRgba ( const SRgb & other,
                          uint8_t      f_a_8ui )
    {
        r = other.r;
        g = other.g;
        b = other.b;
        a = f_a_8ui;
    }
    
    
    inline const SRgba&
    SRgba::operator = ( const SRgb & other )
    {
        r = other.r;
        g = other.g;
        b = other.b;
        a = 255;
        return *this;
    }
    
    /// HSV Color
    struct SHsv
    {
    public:
        
        SHsv() {};
        SHsv ( const float f_h_f, 
               const float f_s_f, 
               const float f_v_f )
        {
            /// Allow continous rotation of hue.
            if (f_h_f > 360)
                h = f_h_f - ((int)(f_h_f/360.f)) * 360.f;
            else if (f_h_f < 0)
                h = f_h_f + (1+(int)(-f_h_f/360.f)) * 360.f;
            else
                h = f_h_f;
            
            s = std::max(std::min(1.f, f_s_f), 0.f);
            v = std::max(std::min(1.f, f_v_f), 0.f);
        }
        
        const SHsv& operator = ( const SHsv & other )
        {
            h = other.h;
            s = other.s;
            v = other.v;
            return (*this);
        }
        
        bool operator == ( const SHsv & other ) const
        {
            return h == other.h && s == other.s && v == other.v;
        }

        void set (  const float f_h_f, 
                    const float f_s_f, 
                    const float f_v_f )
            
        {
            /// Allow continous rotation of hue.
            if (f_h_f > 360)
                h = f_h_f - ((int)(f_h_f/360.f)) * 360.f;
            else if (f_h_f < 0)
                h = f_h_f + (1+(int)(-f_h_f/360.f)) * 360.f;
             else
                h = f_h_f;
               
            s = std::max(std::min(1.f,   f_s_f), 0.f);
            v = std::max(std::min(1.f,   f_v_f), 0.f);
        }
        
        float h;
        float s;
        float v;
        
    };

    /// HSV Color
    struct SHsl
    {
    public:
        
        SHsl() {};
        SHsl ( const float f_h_f, 
               const float f_s_f, 
               const float f_l_f )
        {
            /// Allow continous rotation of hue.
            if (f_h_f > 360)
                h = f_h_f - ((int)(f_h_f/360.f)) * 360.f;
            else if (f_h_f < 0)
                h = f_h_f + (1+(int)(-f_h_f/360.f)) * 360.f;
            else
                h = f_h_f;

            s = std::max(std::min(1.f,   f_s_f), 0.f);
            l = std::max(std::min(1.f,   f_l_f), 0.f);
        }
        
        const SHsl& operator = ( const SHsl & other )
        {
            h = other.h;
            s = other.s;
            l = other.l;
            return (*this);
        }
        
        bool operator == ( const SHsl & other ) const
        {
            return h == other.h && s == other.s && l == other.l;
        }

        void set (  const float f_h_f, 
                    const float f_s_f, 
                    const float f_l_f )
            
        {
            /// Allow continous rotation of hue.
            if (f_h_f > 360)
                h = f_h_f - ((int)(f_h_f/360.f)) * 360.f;
            else if (f_h_f < 0)
                h = f_h_f + (1+(int)(-f_h_f/360.f)) * 360.f;
            else
                h = f_h_f;

            s = std::max(std::min(1.f,   f_s_f), 0.f);
            l = std::max(std::min(1.f,   f_l_f), 0.f);
        }
        
        float h;
        float s;
        float l;
        
    };

    class CColor
    {
    /// Standard Colors (value assigned in colors.cpp).
    public:        
        static const SRgb white;
        static const SRgb black;
        static const SRgb red;
        static const SRgb blue;
        static const SRgb green;

    public:
        static SRgb getRgbFromHsv ( const SHsv & f_color );

        static SRgb getRgbFromHsl ( const SHsl & f_color );

        static SHsv getHsvFromRgb ( const SRgb & f_color );

        static SHsl getHslFromRgb ( const SRgb & f_color );
        
    };

} /// Namespace QCV

#endif // __COLORS_H
