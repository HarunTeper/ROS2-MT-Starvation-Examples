# ROS2-Multithreaded-Executor-Starvation-Examples

The following content are the example systems in of the multi-threaded in ROS 2 that show starvation, i.e., tasks may never be executed. These results are based on the paper "Thread Carefully: Preventing Starvation in the ROS 2 Multithreaded Executor" by Teper et al. in EMSOFT 2024.

# Setup

The following steps help to setup and run the experiments.

## Requirements

Install [Docker Engine](https://docs.docker.com/engine/install/)

Install [Visual Studio Code](https://code.visualstudio.com/)

## Startup

There are two options for the startup of the container.

### Option 1: Start the Container with Visual Studio Code

In Visual Studio Code, install the **Docker** and **Dev Containers** extensions.

Build and open the container.

### Option 2: Start the Container with Docker

Run the following command in a terminal that is in the current folder's directory:

> docker build -t ros2-application .devcontainer/

Start the container using the following command:

> docker run --network host -it -v .:/home/vscode/workspace ros2-application

# Experiments

Start and enter the Docker or Dev Container.

## Build

To build the ROS 2 packages, you need to build them first. Run the following commands based on your environment.

### Docker

"cd packages && colcon build --symlink-install"

### Dev Container

Press **Ctrl+Shift+P**, type **"Run Task"**, press **Enter**, and select **"ROS2-Build"**

## Run

To run the experiments, use the following commands:

### Docker

Example 4: 

    source packages/install/setup.bash && ros2 launch starvation_examples launch_starvation_examples.launch.py example_number:=4

Example 5: 

    source packages/install/setup.bash && ros2 launch starvation_examples launch_starvation_examples.launch.py example_number:=5

Example 6: 

    source packages/install/setup.bash && ros2 launch starvation_examples launch_starvation_examples.launch.py example_number:=6

### Dev Container

Press **Ctrl+Shift+P**, type **"Run Task"**, press **Enter**, and select from the following options:

    RUN-Example-4
    RUN-Example-5
    RUN-Example-6

## Output

While the experiment is running, you will see two things. 

During startup, there will be the following messages

    [starvation_examples]: Starvation Node Startup
    [starvation_examples]: Example Number: 4
    [starvation_examples]: Timer 2 should never be executed
    [starvation_examples]: Starvation Node Ready
    [starvation_examples]: Starting execution

After that, the following messages will appear (depending on the example number, the number of the timers may change):

    [starvation_examples]: Timer 1 executes
    [starvation_examples]: Timer 3 executes

For starvation, you need to check whether or not the timer that was specified during startup is **never** part of the output messages after the execution starts.

As each timer has a maximum period of 1000ms, it is usually enough to run the experiment for 10 seconds.

The experiments show that the multi-threaded executor suffers from starvation, as some tasks are never executed.
