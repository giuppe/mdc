/***************************************************************************
                   RGB_container.cpp  -  Insert colour information
                             -------------------
    begin                : Dec 13, 2007
    copyright            : Livio Pipitone
    email                : livent@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                                                                 
 *   This program is free software; you can redistribute it and/or modify  
 *   it under the terms of the GNU General Public License, Version 2,        
 *   as published by the Free Software Foundation.                                  
 *                                                                                                                 
 ***************************************************************************/

#include "RGB_container.h"

RGB_container::RGB_container(){}
RGB_container::~RGB_container(){}
void RGB_container::set_x_position(Uint16 position) {x_position = position;}
Uint16 RGB_container::get_x_position() const {return x_position;}
void RGB_container::set_y_position(Uint16 position) {y_position = position;}
Uint16 RGB_container::get_y_position() const {return y_position;}
void RGB_container::setBlue_value(Uint8 value) {blue_value = value;}
Uint8 RGB_container::getBlue_value() const {return blue_value;}
void RGB_container::setGreen_value(Uint8 value) {green_value = value;}
Uint8 RGB_container::getGreen_value() const {return green_value;}
void RGB_container::setRed_value(Uint8 value) {red_value = value;}
Uint8 RGB_container::getRed_value() const {return red_value;}
