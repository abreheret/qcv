/*
 * Copyright (C) 2012 Hernan Badino <hernan.badino@gmail.com>
 *
 * This file is part of QCV
 *
 * QCV is under the terms of the GNU Lesser General Public License
 * version 3. See the GNU LGPL version 3 for details.
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


/*@@@**************************************************************************
* \file  enumParamBase
* \author Hernan Badino
* \notes 
*******************************************************************************
*****          (C) COPYRIGHT Hernan Badino - All Rights Reserved          *****
******************************************************************************/

/* INCLUDES */
#include "enumParamBase.h"

using namespace QCV;

/// Constructors/Destructor
CEnumParameterBase::CEnumParameterBase (  std::string               f_name_str,
                                          std::string               f_comment_str,
                                          CParameterBaseConnector * f_connector_p )
        : CParameter(f_name_str, f_comment_str, f_connector_p )
{}

CEnumParameterBase::~CEnumParameterBase () 
{}

/// Get and set values from strings.
std::string
CEnumParameterBase::getStringFromValue ( ) const
{ 
    return ""; 
}

bool
CEnumParameterBase::setValueFromString ( std::string /*f_val_str*/ )
{ 
    return false; 
}

/// Get editor.
QWidget *
CEnumParameterBase::createEditor ( )
{ 
    return NULL; 
}

