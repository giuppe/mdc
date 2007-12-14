/***************************************************************************
           			RGB_container.h  - Colours management class
                             -------------------
    begin                : Dec 14, 2007
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

#include "defs.h"

#ifndef RGB_CONTAINER_H_
#define RGB_CONTAINER_H_

class RGB_container {
private:
	Uint8 red_value;
	Uint8 green_value;
	Uint8 blue_value;
	Uint16 x_position;
	Uint16 y_position;
public:
	RGB_container();
	~RGB_container();
	
	/*
	 * Sets orizontal position of a pixel.
	 * @position: orizontal position
	 */
	void set_x_position(Uint16 position);

	/*
	 * Gets orizontal position of a pixel.
	 * @returns: orizontal position
	 */
	Uint16 get_x_position() const;

	/*
	 * Sets vertical position ofa pixel.
	 * @position: vertical position
	 */
	void set_y_position(Uint16 position);
	
	/*
	 * Gets vertical position of a pixel.
	 * @returns: orizontal position
	 */
	Uint16 get_y_position() const;

	/*
	 * Sets blue colour component of a pixel.
	 * @blue_value: blue colour value
	 */
	void setBlue_value(Uint8 value);

	/*
	 * Gets blue colour component of a pixel.
	 * @returns: blue colour value
	 */
	Uint8 getBlue_value() const;

	/*
	 * Sets green colour component of a pixel.
	 * @green_value: green colour value
	 */
	void setGreen_value(Uint8 value);

	/*
	 * Sets green colour component of a pixel.
	 * @returns: green colour value
	 */
	Uint8 getGreen_value() const;

	/*
	 * Sets red colour component of a pixel.
	 * @red_value: red colour value
	 */
	void setRed_value(Uint8 value);

	/*
	 * Sets red colour component of a pixel.
	 * @returns: red colour value
	 */
	Uint8 getRed_value() const;
};

#endif /*RGB_CONTAINER_H_*/
