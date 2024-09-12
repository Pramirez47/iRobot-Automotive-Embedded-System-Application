# iRobot-Automotive-Embedded-System-Application

</center>

- Ponciano Ramirez
- Gage Moorman

## Project Description:

Users should be able to order food anytime they are working; thus, our robot will be tasked to
ensure this is accomplished. The robot will grab the employee’s order and then navigate to a
location where an individual sits. The robot will do this task while simultaneously avoiding any
obstacles that may be in the way, as such obstacles could prevent the robot from accomplishing
this goal.

Our motivation is to satisfy the employee’s want of enjoying food while at the same time still
being able to focus on whatever task they are doing. Allowing workers to perform their tasks
more effectively while they are full of food will also increase morale, as anybody can order food
anytime while doing their work. Additionally, it will allow employees to work without taking a
lunch break, which will help them to collect more work hours.

Our approach to creating this application was to determine what consumers would want to
begin with. We understand the want of enjoying a meal while still being able to work to not
interrupt our tasks and creative workflow. Upon understanding what the goal of our robot is, we
will then create the application itself to handle the task

## Functional Requirements:

- Use infrared (IR) and ultrasonic (Ping) sensors to gather environmental data.
- Employ a bumper sensor to detect and avoid obstacles.
- Present key information to the operator on an LCD display.
- Navigate to the target location while avoiding elevation changes (e.g., holes) and staying within predefined paths and boundaries.
- Transmit data for remote monitoring through Putty.
- Operate in both manual and autonomous modes.
- Bypass obstacles within defined distances and along designated routes.

## Demonstration Narrative:

Our CyBot will demonstrate driving/delivering in an office environment, school classroom, or
construction zone, where people are walking around and busy working on many different things.
There will be many desks, chairs, plants, and other obstacles in the way of the CyBot between
the package pickup and dropoff. There is also a large hole in the middle of the room, which acts
as a hazard for the robot, which can damage it and cause it to break, failing to deliver the
package. The test area will have tape surrounding it, simulating walls or bounds, where if the
robot leaves, the person will never receive what they ordered. It is also very important that the
CyBot does not try to fit into areas it cannot go to because it can get stuck, causing it to be
unable to deliver the package.
