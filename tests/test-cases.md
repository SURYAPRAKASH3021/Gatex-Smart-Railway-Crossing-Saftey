Gatex – Test Cases

Purpose

These test cases define how the educational railway-crossing prototype should be evaluated. Results must be recorded after actual testing.

Test ID| Scenario| Expected Result
TC01| No train input| Model gate remains open; alerts are off
TC02| Train input activated| Model gate closes; warning LED turns on
TC03| Train input active and obstacle detected within 20 cm| Model gate remains closed; buzzer activates
TC04| Obstacle outside detection threshold| Obstacle alert remains off
TC05| Ultrasonic sensor returns no valid reading| Distance is treated as invalid; further safety handling requires improvement
TC06| Train input deactivated| Model gate opens and alerts turn off

Test Status

Status: Not yet physically tested.

Limitations

These tests describe expected behaviour of a classroom model. They do not establish railway safety certification or suitability for real railway crossings.
