from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import yaml
import os

def generate_launch_description():

    config_file_path = os.path.join(
        get_package_share_directory('map_changer2'),
        'config',
        'map_list.yaml'
    )

    with open(config_file_path, 'r') as file:
        launch_params = yaml.safe_load(file)['map_list']

    map_change_node = Node(
        package = 'map_changer2',
        namespace = 'map_changer2',
        executable = 'map_changer',
        parameters = [{'map_name': config_file_path}],
        output = 'screen'
    )

    return LaunchDescription([map_change_node])