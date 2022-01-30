#include "StepperDrivers.hpp"
#include <Arduino.h>

enum MotorPinOps {
  CCW = 0,//Counterclockwise direction equates to setting dir_pin to LOW/0
  CW = 1,//Clockwise direction equates to setting dir_pin to HIGH/1
  ENABLE = 0,//Enable is zero because the driver activates the enable pin on a low signal
  DISABLE = 1//Driver disables movement when enable pin receives a high signal
};


TB6600::TB6600(int dir_pin, int pul_pin, int ena_pin)
{
	m_direction_pin = dir_pin;//Pin is set either high or low to set direction of the motor
	m_pulse_pin = pul_pin;//Pin is toggled to send signal to the driver to move
	m_enable_pin = ena_pin;//Pin is pulled low to enable the stepper//Can be hard wired to ground if always enabled stepper is desired


	pinMode(m_direction_pin, OUTPUT);//Set dir pin to send output signals
	pinMode(m_pulse_pin, OUTPUT);//Set pulse pin to send output signals
	pinMode(m_enable_pin, OUTPUT);//Set enable pin to send output signals

	digitalWrite(m_enable_pin, LOW);//Set the enable pin to low to enable movement;
	digitalWrite(m_direction_pin, LOW);//Sets stepper revolution direction. For this motor, setting dir_pin to high moves the motor ccw when facing shaft and cw when looking from behind.
									   //Set default to cw from behind

	m_rot_dir = 3;//Set startup default direction holder to a non used value to avoid unexpected startup behavior
	m_use_inverted_direction = false;//Set default direction to normal rotation. Set to true to invert rotation directions in all functions
	m_pulse_delay = 120;//Set the signal pulse delay in microseconds
	//m_steps_per_rev = 200;//Set default steps per revolution to 200 [Used in Beta. Let user declare in own program]
	m_absolute_steps = 0;//Used to save the absolute movement of steps from 0
	m_step_flag = false;//Set default to false for the first function that will use this
}

void TB6600::RotateCW()
{
	if(m_use_inverted_direction == true)//Use opposite direction incase wired direction is reversed
	{
		if(m_rot_dir != CCW)
		{
				digitalWrite(m_direction_pin,CCW);//Set direction to CCW (when motor shaft is facing away)
				m_rot_dir = CCW;
		}
	}
	else//Normal Operation
	{
		if(m_rot_dir != CW)
		{
				digitalWrite(m_direction_pin,CW);//Set direction to CCW (when motor shaft is facing away)
				m_rot_dir = CW;
		}
	}
			/************
			 ************
			 ***********/
			StepPulse();
			/************
			*************
			************/
			m_absolute_steps++;
}

void TB6600::RotateCCW()
{
	if(m_use_inverted_direction == true)//Use opposite direction incase wired direction is reversed
	{
		if(m_rot_dir != CW)
		{
				digitalWrite(m_direction_pin,CW);//Set direction to CCW (when motor shaft is facing away)
				m_rot_dir = CW;
		}
	}
	else//Normal Operation
	{
		if(m_rot_dir != CCW)
		{
				digitalWrite(m_direction_pin,CCW);//Set direction to CCW (when motor shaft is facing away)
				m_rot_dir = CCW;
		}
	}
			/************
			 ************
			 ***********/
			StepPulse();
			/************
			*************
			************/
			m_absolute_steps--;
}

/////////

int TB6600::RotateSteps(long long int steps, bool blocking)
{

	//Use the if statment to decide directions based on the sign of steps. Counting will be done with the absolute value of steps
	if(m_use_inverted_direction == true)//Use opposite direction incase wired direction is reversed
	{
		if(m_rot_dir != CW && steps < 0)
		{
				digitalWrite(m_direction_pin,CW);//Set direction to CCW (when motor shaft is facing away)
				m_rot_dir = CW;
		}

		if(m_rot_dir != CCW && steps > 0)
		{
				digitalWrite(m_direction_pin,CCW);//Set direction to CCW (when motor shaft is facing away)
				m_rot_dir = CCW;
		}
	}
	else//Normal Operation
	{
		if(m_rot_dir != CW && steps > 0)
		{
				digitalWrite(m_direction_pin,CW);//Set direction to CCW (when motor shaft is facing away)
				m_rot_dir = CW;
		}

		if(m_rot_dir != CCW && steps < 0)
		{
				digitalWrite(m_direction_pin,CCW);//Set direction to CCW (when motor shaft is facing away)
				m_rot_dir = CCW;
		}
	}

	if(blocking == true && m_step_flag == false)
		{
			for(long long int i = 0; i < abs(steps); i++)
			{
				/************
				 ************
				***********/
				StepPulse();
				/************
				*************
				************/
				m_step_count++;
				if(steps < 0)
				{
					m_absolute_steps--;
				}
				else{
					m_absolute_steps++;
				}
			}
			m_step_count = 0;
			m_step_flag = true;
			return 0;
		}
		else
		{
			if(m_step_count < abs(steps) && m_step_flag == false)
			{
				/************
				 ************
				***********/
				StepPulse();
				/************
				*************
				************/
				m_step_count++;
				if(steps < 0)
				{
					m_absolute_steps--;
				}
				else{
					m_absolute_steps++;
				}
			}
			else if (m_step_count >= abs(steps))
			{
				m_step_count = 0;
				m_step_flag = true;
				return 0;
			}
		}

return -1;//Return that steps are not complete

}

//////////////////////////////////////////////////

void TB6600::StepPulse()
{
	digitalWrite(m_pulse_pin, LOW);
	digitalWrite(m_pulse_pin, HIGH);//Pin is driven by rising edge. Must set low, then high each time to move one step
	delayMicroseconds(m_pulse_delay);//Set delay between pulses(steps)
}

void TB6600::SetPulseDelayMicroseconds(int dly)
{
	m_pulse_delay = dly;
}

/*[Used in Beta. Let user declare in own program]
void TB6600::SetStepsPerRevolution(int steps)
{
	m_steps_per_rev = steps;
}*/

void TB6600::UseInvertedDirection()
{
	m_use_inverted_direction = true;
}

void TB6600::ClearFlags()
{
	m_step_flag = false;
}

long long int TB6600::GetAbsoluteSteps()
{
	return m_absolute_steps;
}

void TB6600::DisableMotor()
{
	digitalWrite(m_enable_pin, DISABLE);//Disable Motor
}

void TB6600::EnableMotor()
{
	digitalWrite(m_enable_pin, ENABLE);//Enable Motor
}