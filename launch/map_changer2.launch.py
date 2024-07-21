from launch import LaunchDescription
from launch_ros.actions import Node
import os

def generate_launch_description():

    config_file_path = os.path.join(
        get_package_share_directory('map_changer2'),
        'config',
        'map_list.yaml'
    )

    with open(config_file_path, 'r') as file:
        launch_params = yaml.safe_load(file)['launch']

    map_change_node = Node(
        package = 'map_changer2',
        namespace = 'map_changer2'
        executable = 'map_changer',
        parameters = [config_file_path],
        output = 'screen'
    )

    return launch.LaunchDescription([map_changer])