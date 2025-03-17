if [[ $1 = "install" ]]; then
  sudo xbps-install -Syu Vulkan-Headers Vulkan-Tools Vulkan-ValidationLayers vulkan-loader vulkan-loader-devel 
  sudo xbps-install -Syu glfw glfw-devel glfw-wayland
  sudo xbps-install -Syu glm
  sudo xbps-install -Syu shaderc
elif [[ $1 = "remove" ]]; then
  sudo xbps-remove -y Vulkan-Headers Vulkan-Tools Vulkan-ValidationLayers vulkan-loader vulkan-loader-devel
  sudo xbps-remove -y glfw glfw-devel glfw-wayland
  sudo xbps-remove -y glm
  sudo xbps-remove -y shaderc
else 
  echo "no option selected"
fi


