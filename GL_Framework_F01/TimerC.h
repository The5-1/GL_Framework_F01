#pragma once

#include "ForwardDeclarations.h"
#include "GL_include.h"
#include "IComponent.h"

namespace The5 {

	/** Component that provides a timer that is constantly incremented */
	class TimerC : public IComponent
	{
	public:
		///public Fields

		///Constructor / Destructor
		/** Constructor, window to get the time from */
		TimerC(Entity* parentEntity) : IComponent(parentEntity) {};

		///Getters / Setters
		/** implement pure virtual get Type */
		ComponentType getType() override { return ComponentType::TimerCType; };
		/** static method to get global GLFW time */
		static double getWorldTimeInSeconds() { return glfwGetTime(); };
		/** get this timers time */
		double getTimeInSeconds() { return totalTime; };

		///Methods
		/** start the timer */
		void start() { isRunning = true; };
		/** pause the timer */
		void pause() { isRunning = false; };
		/** reset the stored time to 0 */
		void reset() { totalTime = 0.0; };
		/** set the stored time to a given value, if scaled = true, the timers scaling is applied */
		void set(double time, bool scaled = false) 
		{ 
			if (!scaled) { totalTime = time; return; }
			else { totalTime = time*timeScale; return; }
		};
		/** modify the time by the given value, if scaled = true, the timers scaling is applied  */
		void modify(double time, bool scaled = false)
		{ 
			if (!scaled) { totalTime += time; return; }
			else { totalTime += time*timeScale; return; }
		};

	protected:
		///private Fields
		/** running */
		bool isRunning = true;
		/** speed */
		double timeScale = 1.0;
		/** total time */
		double totalTime = 0.0;

		///private Methods
		/** update total time */
		void updateTimer(double delta) {totalTime += delta*timeScale;}

	};
}