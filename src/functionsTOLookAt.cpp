
//calls moveToTargetSimple function
void moveToTargetDisSimple(float a, float d, float ys, float xs, byte power, byte startPower, float maxErrX, float decelEarly, byte decelPower, float dropEarly, tStopType stopType, tMttMode mode, bool velSafety){
	moveToTargetSimple(ys + d * cos(a), xs + d * sin(a), ys, xs, power, startPower, maxErrX, decelEarly, decelPower, dropEarly, stopType, mode, false);
}

//turnDir is the turn direction (ccw or cw). a is angle.
void turnToAngleNewAlg(float a, tTurnDir turnDir, float fullRatio, byte coastPower, float stopOffsetDeg, bool mogo, bool harshStop, bool velSafety){
	if (LOGS) writeDebugStreamLine("Turning to %f", radToDeg(a));

	int velSafetyCounter = 0;

	if (turnDir == ch)
		if (fmod(a - gPosition.a, PI * 2) > PI) turnDir = ccw; else turnDir = cw;

	float endFull;

	unsigned long timeStart = nPgmTime;

	switch (turnDir)
	{
	case cw:
		a = gPosition.a + fmod(a - gPosition.a, PI * 2);
		endFull = gPosition.a * (1 - fullRatio) + a * fullRatio;
		setDrive(127, -127);
		while (gPosition.a < endFull /*&& (velSafety? NOT_SAFETY(power, turnToAngleNewAlg) : 1 )*/)


		{
			if (DATALOG_TURN != -1)
			{
				tHog();
				datalogDataGroupStart();
				datalogAddValue(DATALOG_TURN + 0, radToDeg(gPosition.a));
				datalogAddValue(DATALOG_TURN + 1, 127);
				datalogDataGroupEnd();
				tRelease();
			}
			sleep(10);
		}
		setDrive(coastPower, -coastPower);
		timeStart = nPgmTime;
		while (gPosition.a < a - degToRad(stopOffsetDeg) /* && (velSafety? NOT_SAFETY(power, turnToAngleNewAlg) : 1 ) */)
		{
			if (DATALOG_TURN != -1)
			{
				tHog();
				datalogDataGroupStart();
				datalogAddValue(DATALOG_TURN + 0, radToDeg(gPosition.a));
				datalogAddValue(DATALOG_TURN + 1, 127);
				datalogDataGroupEnd();
				tRelease();
			}
			sleep(10);
		}
		if (LOGS) writeDebugStreamLine("Turn done: %d",  gPosition.a);
		if (harshStop)
		{
			setDrive(-20, 20);
			sleep(150);
			if (LOGS) writeDebugStreamLine("Break done: %d",  gPosition.a);
		}
		setDrive(0, 0);
		break;
	case ccw:
		a = gPosition.a - fmod(gPosition.a - a, PI * 2);
		endFull = gPosition.a * (1 - fullRatio) + a * fullRatio;
		setDrive(-127, 127);
		while (gPosition.a > endFull /* && (velSafety? NOT_SAFETY(power, turnToAngleNewAlg) : 1 )*/)
		{
			if (DATALOG_TURN != -1)
			{
				tHog();
				datalogDataGroupStart();
				datalogAddValue(DATALOG_TURN + 0, radToDeg(gPosition.a));
				datalogAddValue(DATALOG_TURN + 1, 127);
				datalogDataGroupEnd();
				tRelease();
			}
			sleep(10);
		}
		setDrive(-coastPower, coastPower);
		timeStart = npgmTime;
		while (gPosition.a > a + degToRad(stopOffsetDeg)/* && (velSafety? NOT_SAFETY(power, turnToAngleNewAlg) : 1)*/)
	   {
			if (DATALOG_TURN != -1)
			{
				tHog();
				datalogDataGroupStart();
				datalogAddValue(DATALOG_TURN + 0, radToDeg(gPosition.a));
				datalogAddValue(DATALOG_TURN + 1, 127);
				datalogDataGroupEnd();
				tRelease();
			}
			sleep(10);
		}
		if (LOGS) writeDebugStreamLine("Turn done: %d",  gPosition.a);
		if (harshStop)
		{
			setDrive(20, -20);
			sleep(150);
			if (LOGS) writeDebugStreamLine("Break done: %d",  gPosition.a);
		}
		setDrive(0, 0);
		break;
	}
	if (LOGS) writeDebugStreamLine("Turned to %f | %f %f %f", radToDeg(a), gPosition.y, gPosition.x, radToDeg(gPosition.a));
}

//turns robot to new angle. No PID used oddly
void turnToTargetNewAlg(float y, float x, tTurnDir turnDir, float fullRatio, byte coastPower, float stopOffsetDeg, bool mogo, bool harshStop, float offset, bool velSafety){
	if (LOGS) writeDebugStreamLine("Turning to %f %f", y, x);

	if (turnDir == ch)
		if (fmod(atan2(x - gPosition.x, y - gPosition.y) + offset - gPosition.a, PI * 2) > PI) turnDir = ccw; else turnDir = cw;

	float endFull, target;

	int velSafetyCounter = 0;
	unsigned long timeStart =  nPgmTime;

	switch (turnDir)
	{
	case cw:
		target = gPosition.a + fmod(atan2(x - gPosition.x, y - gPosition.y) + offset - gPosition.a, PI * 2);
		endFull = gPosition.a * (1 - fullRatio) + target * fullRatio;
		if (LOGS) writeDebugStreamLine("%f %f", radToDeg(target), radToDeg(endFull));
		setDrive(127, -127);
		while (gPosition.a < endFull /*&& (velSafety? NOT_SAFETY(power, turnToTargetNewAlg) : 1 )*/)
    {
			if (DATALOG_TURN != -1)
			{
				tHog();
				datalogDataGroupStart();
				datalogAddValue(DATALOG_TURN + 0, radToDeg(gPosition.a));
				datalogAddValue(DATALOG_TURN + 1, 127);
				datalogDataGroupEnd();
				tRelease();
			}
			sleep(10);
		}
		setDrive(coastPower, -coastPower);
		timeStart = npgmTime;
		while (gPosition.a < nearAngle(atan2(x - gPosition.x, y - gPosition.y) + offset, target) - degToRad(stopOffsetDeg) /*&& (velSafety? NOT_SAFETY(power, turnToTargetNewAlg) : 1 )*/)
    {
			if (DATALOG_TURN != -1)
			{
				tHog();
				datalogDataGroupStart();
				datalogAddValue(DATALOG_TURN + 0, radToDeg(gPosition.a));
				datalogAddValue(DATALOG_TURN + 1, 127);
				datalogDataGroupEnd();
				tRelease();
			}
			sleep(10);
		}
		if (LOGS) writeDebugStreamLine("Turn done: %d",  gPosition.a);
		if (harshStop)
		{
			setDrive(-20, 20);
			sleep(150);
			if (LOGS) writeDebugStreamLine("Break done: %d",  gPosition.a);
		}
		setDrive(0, 0);
		break;
	case ccw:
		target = gPosition.a - fmod(gPosition.a - atan2(x - gPosition.x, y - gPosition.y) - offset, PI * 2);
		endFull = gPosition.a * (1 - fullRatio) + (target) * fullRatio;
		if (LOGS) writeDebugStreamLine("%f %f", radToDeg(target), radToDeg(endFull));
		setDrive(-127, 127);
		while (gPosition.a > endFull /*&& (velSafety? NOT_SAFETY(power, turnToTargetNewAlg) : 1 )*/)
	   {
			if (DATALOG_TURN != -1)
			{
				tHog();
				datalogDataGroupStart();
				datalogAddValue(DATALOG_TURN + 0, radToDeg(gPosition.a));
				datalogAddValue(DATALOG_TURN + 1, 127);
				datalogDataGroupEnd();
				tRelease();
			}
			sleep(10);
		}
		setDrive(-coastPower, coastPower);
		timeStart = nPgmTime;
		while (gPosition.a > nearAngle(atan2(x - gPosition.x, y - gPosition.y) + offset, target) + degToRad(stopOffsetDeg) /*&& (velSafety? NOT_SAFETY(power, turnToTargetNewAlg) : 1 )*/)
    {
			if (DATALOG_TURN != -1)
			{
				tHog();
				datalogDataGroupStart();
				datalogAddValue(DATALOG_TURN + 0, radToDeg(gPosition.a));
				datalogAddValue(DATALOG_TURN + 1, 127);
				datalogDataGroupEnd();
				tRelease();
			}
			sleep(10);
		}
		if (LOGS) writeDebugStreamLine("Turn done: %d",  gPosition.a);
		if (harshStop)
		{
			setDrive(20, -20);
			sleep(150);
			if (LOGS) writeDebugStreamLine("Break done: %d",  gPosition.a);
		}
		setDrive(0, 0);
		break;
	}
	if (LOGS) writeDebugStreamLine("Turned to %f %f | %f %f %f", y, x, gPosition.y, gPosition.x, radToDeg(gPosition.a));
}

//makes sweeping path with robot
void sweepTurnToTarget(float y, float x, float a, float r, tTurnDir turnDir, byte power, bool slow, bool velSafety)
{
	sVector vector;
	sPolar polar;
	int velSafetyCounter = 0;

	if (turnDir == ch)
	{
		vector.x = gPosition.x - x;
		vector.y = gPosition.y - y;
		vectorToPolar(vector, polar);
		polar.angle += a;
		polarToVector(polar, vector);

		turnDir = vector.x > 0 ? cw : ccw;
	}

	float yOrigin, xOrigin;
	float linearV, angularV, angularVLast = 0;
	float localR, localA;

	const float kR = 15.0;
	const float kA = 5.0;
	const float kB = 60.0;
	const float kP = 30.0;
	const float kD = 2000.0;

	sCycleData cycle;
	initCycle(cycle, 40, "sweepTurnToTarget");

	unsigned long timeStart = nPgmTime;
	switch (turnDir)
	{
	case cw:
		vector.y = 0;
		vector.x = r;
		vectorToPolar(vector, polar);
		polar.angle -= a;
		polarToVector(polar, vector);
		yOrigin = y + vector.y;
		xOrigin = x + vector.x;

		localA = atan2(gPosition.x - xOrigin, gPosition.y - yOrigin);

		a = nearAngle(a, power > 0 ? gPosition.a : (gPosition.a + PI));

		if (LOGS) writeDebugStreamLine("%d Sweep to %f around %f %f", nPgmTime, radToDeg(a), yOrigin, xOrigin);

		do
		{
			float aGlobal = gPosition.a;
			if (power < 0)
				aGlobal += PI;
			angularV = gVelocity.a;
			float _y = gPosition.y - yOrigin;
			float _x = gPosition.x - xOrigin;
			localR = sqrt(_y * _y + _x * _x);
			localA = nearAngle(atan2(_x, _y), localA);
			linearV = gVelocity.x * sin(localA + PI / 2) + gVelocity.y * cos(localA + PI / 2);

			float target = MAX(linearV, 15) / localR + kR * log(localR / r) + kA * (nearAngle(localA + PI / 2, aGlobal) - aGlobal);
			word turn = round(kB * target + kP * (target - angularV) + kD * (angularVLast - angularV) / 40);
			angularVLast = angularV;

			if (turn < 0)
				turn = 0;
			else if (turn > 150)
				turn = 150;

			if (power > 0)
				setDrive(power, power - turn);
			else
				setDrive(power + turn, power);

			if (DATALOG_SWEEP != -1)
			{
				tHog();
				datalogDataGroupStart();
				datalogAddValue(DATALOG_SWEEP + 0, localR * 100);
				datalogAddValue(DATALOG_SWEEP + 1, radToDeg(localA) * 10);
				datalogAddValue(DATALOG_SWEEP + 2, radToDeg(target) * 10);
				datalogAddValue(DATALOG_SWEEP + 3, turn * 10);
				datalogAddValue(DATALOG_SWEEP + 4, linearV * 10);
				datalogAddValue(DATALOG_SWEEP + 5, radToDeg(angularV) * 10);
				datalogDataGroupEnd();
				tRelease();
			}

			endCycle(cycle);
		} while ((power > 0 ? gPosition.a : (gPosition.a + PI)) - a < (slow ? -0.1 : -0.15) && (velSafety? NOT_SAFETY(power, sweepTurnToTarget) : 1 ));
		break;
	case ccw:
		vector.y = 0;
		vector.x = r;
		vectorToPolar(vector, polar);
		polar.angle += a;
		polarToVector(polar, vector);
		yOrigin = y + vector.y;
		xOrigin = x + vector.x;

		localA = atan2(gPosition.x - xOrigin, gPosition.y - yOrigin);

		a = nearAngle(a, power > 0 ? gPosition.a : (gPosition.a + PI));

		if (LOGS) writeDebugStreamLine("%d Sweep to %f around %f %f", nPgmTime, radToDeg(a), yOrigin, xOrigin);

		do
		{
			float aGlobal = gPosition.a;
			if (power < 0)
				aGlobal += PI;
			angularV = gVelocity.a;
			float _y = gPosition.y - yOrigin;
			float _x = gPosition.x - xOrigin;
			localR = sqrt(_y * _y + _x * _x);
			localA = nearAngle(atan2(_x, _y), localA);
			linearV = gVelocity.x * sin(localA - PI / 2) + gVelocity.y * cos(localA - PI / 2);

			float target = -MAX(linearV, 15) / localR + kR * log(r / localR) + kA * (nearAngle(localA - PI / 2, aGlobal) - aGlobal);
			word turn = round(kB * target + kP * (target - angularV) + kD * (angularVLast - angularV) / 40);
			angularVLast = angularV;

			if (turn > 0)
				turn = 0;
			else if (turn < -150)
				turn = -150;

			if (power > 0)
				setDrive(power + turn, power);
			else
				setDrive(power, power - turn);

			if (DATALOG_SWEEP != -1)
			{
				tHog();
				datalogDataGroupStart();
				datalogAddValue(DATALOG_SWEEP + 0, localR * 100);
				datalogAddValue(DATALOG_SWEEP + 1, radToDeg(localA) * 10);
				datalogAddValue(DATALOG_SWEEP + 2, radToDeg(target) * 10);
				datalogAddValue(DATALOG_SWEEP + 3, turn * 10);
				datalogAddValue(DATALOG_SWEEP + 4, linearV * 10);
				datalogAddValue(DATALOG_SWEEP + 5, radToDeg(angularV) * 10);
				datalogDataGroupEnd();
				tRelease();
			}

			endCycle(cycle);
		} while ((power > 0 ? gPosition.a : (gPosition.a + PI)) - a > (slow ? 0.1 : 0.15) && (velSafety? NOT_SAFETY(power, moveToTargetSimple) : 1));
		break;
	}
	setDrive(0, 0);
	if (LOGS) writeDebugStreamLine("%d Done sweep turn", nPgmTime);
}
