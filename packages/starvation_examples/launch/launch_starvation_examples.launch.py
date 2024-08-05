"""ROS2 Launch file"""

from launch_ros.actions import Node
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration


def generate_launch_description():
    """Returns launch description"""

    # add launch configuration for example number
    example_number = LaunchConfiguration(
        'example_number',
        default='4'
    )

    # declare launch configuration
    example_number_arg = DeclareLaunchArgument(
        'example_number',
        default_value='4',
        description='Example number to run'
    )

    # Nodes
    publisher_node = Node(
        package='starvation_examples',
        executable='starvation_examples',
        name='starvation_examples',
        output='screen',
        parameters=[{'example_number': example_number}]
    )

    # Launch Description
    launch_description = LaunchDescription()

    launch_description.add_action(publisher_node)
    launch_description.add_action(example_number_arg)

    return launch_description
