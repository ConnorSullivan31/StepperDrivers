#ifndef STEPPERDRIVERS_HPP
#define STEPPERDRIVERS_HPP

class TB6600
{

	public:
		TB6600(int dir_pin, int pul_pin, int ena_pin);//5,6,7

		void RotateCW();//Call in a loop for continuous rotation
		void RotateCCW();//Call in a loop for continuous rotation
		int RotateSteps(long long int steps, bool blocking = false);//Call in loop to move a certain ammount in either direction or use blocking
		int RotateStepsCW(unsigned long long int steps, bool blocking = false);//Call in loop to move a certain ammount of steps each call or use blocking
		int RotateStepsCCW(unsigned long long int steps, bool blocking = false);//Call in loop to move a certain ammount of steps each call or use blocking
		int RotateRevsCW(float revs, bool blocking = false);//Call in loop to move a certain ammount of steps each call
		int RotateRevsCCW(float revs, bool blocking = false);//Call in loop to move a certain ammount of steps each call
		void SetPulseDelayMicroseconds(int dly);//Sets the steppers pulse delay
		void SetStepsPerRevolution(int steps);//Sets the ammount of steps in one revolution
		void UseInvertedDirection();//Call this in setup to invert the direction of all functions



	private:

		void StepPulse();//Sends a pulse signal to stepper

		int m_direction_pin, m_pulse_pin, m_enable_pin;//holds the pins used to reference the stepper
		int m_rot_dir;//Stores the current rotation direction
		int m_pulse_delay;//Stores the delay between signal pulses
		unsigned long long int m_step_count;//Stores the step count for a function
		long long int m_absolute_steps;//[CW +][CCW -]	
		unsigned long long int m_steps_per_rev;//Stores the steps per rev for the stepper
		bool m_use_inverted_direction;//Swaps CW and CWW if wiring or driver is backwards
		bool m_sequence_finished;//Saves whether the called funciton has completed its steps


};




#endif //STEPPERDRIVERS_HPP