#include <cstdint>
#include <cstdlib>
#include <vulkan/vulkan_core.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <vector>
#include <iostream>

//#define NOVKDEBUG
#ifdef NOVKDEBUG
  static const bool enableValiationLayers = false;
#else
  static const bool enableValiationLayers = true;
#endif
const uint32_t validationLayers_count = 0;
const char* validationLayers[validationLayers_count] = {
  
};

static const uint32_t DEFAULT_WINDOW_WIDTH = 800;
static const uint32_t DEFAULT_WINDOW_HEIGHT = 600;
static const char CONST_APPLICATION_NAME[] = "Hello Triangle";
static const char CONST_ENGINE_NAME[] = "osmium";

void initWindow(GLFWwindow *window) {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  window = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, "Vulkan", NULL, NULL);
  return;
}

bool checkValidationLayerSupport() {
  uint32_t layerCount;
  vkEnumerateInstanceLayerProperties(&layerCount, NULL);
  VkLayerProperties availableLayers[layerCount];
  vkEnumerateInstanceLayerProperties(&layerCount, availableLayers);

  for( const char* layerName: validationLayers) {
    bool layerFound = false;
    for(const VkLayerProperties &LayerProperties : availableLayers) {
      printf("\%s\n",LayerProperties.layerName);
      if(strcmp(layerName, LayerProperties.layerName) == 0) {
        layerFound = true;
        break;
      }
    }
    if (!layerFound) {
      return false;
    }
  }
  return true;
}


std::vector<const char*> getRequiredExtensions() {
  uint32_t glfwExtensionCount = 0;
  const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  std::vector<const char*> extensions(glfwExtensions, glfwExtensions+ glfwExtensionCount);
  
  if (enableValiationLayers) {
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
  }

  return extensions;

}


void createInstance(VkInstance *instance) {
  if (enableValiationLayers && !checkValidationLayerSupport()) {
    fprintf(stderr, "[PANIC] validation layers requested, but not available!");
    exit(EXIT_FAILURE);
  }
  VkApplicationInfo appInfo{};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = CONST_APPLICATION_NAME;
  appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
  appInfo.pEngineName = "osmium";
  appInfo.apiVersion = VK_API_VERSION_1_3;
 
  VkInstanceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;
  
  if (enableValiationLayers) {
    createInfo.enabledLayerCount = validationLayers_count;
    createInfo.ppEnabledLayerNames = validationLayers;
  } 
  else {
    createInfo.enabledLayerCount = 0;
  }
  
  std::vector<const char*> extensions = getRequiredExtensions();
  createInfo.enabledExtensionCount = extensions.size();
  createInfo.ppEnabledExtensionNames = extensions.data();
  

  VkResult result = vkCreateInstance(&createInfo, NULL, instance);
  if(result != VK_SUCCESS) {
    fprintf(stderr,"failed to create instance!");
    exit(EXIT_SUCCESS);
  } 
}

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
  VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
  VkDebugUtilsMessageTypeFlagsEXT messageType,
  const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
  void* pUserData) {
  
  fprintf(stderr,"validation layer: %s\n", pCallbackData->pMessage);
  return VK_FALSE;

}

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
                                      const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                      const VkAllocationCallbacks* pAllocator,
                                      VkDebugUtilsMessengerEXT* pDebugMessenger) {
  auto func =
    (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
  if(func != nullptr) {
    return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
  } else {
    return VK_ERROR_EXTENSION_NOT_PRESENT;
  }
  
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance,
                                       VkDebugUtilsMessengerEXT debugMessenger,
                                      const VkAllocationCallbacks* pAllocator) {
  auto func =
    (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
  if(func != nullptr) {
    func(instance, debugMessenger, pAllocator);
  }
}



void setupDebugMessenger(VkInstance* instance,VkDebugUtilsMessengerEXT* debugMessenger) {
  if (!enableValiationLayers) return;
  VkDebugUtilsMessengerCreateInfoEXT createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  createInfo.messageSeverity = 
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | 
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  createInfo.messageType = 
    VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | 
    VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | 
    VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  createInfo.pfnUserCallback = debugCallback;
  createInfo.pUserData = nullptr;

  if(CreateDebugUtilsMessengerEXT(*instance, &createInfo, nullptr, debugMessenger) != VK_SUCCESS) {
    fprintf(stderr, "failed to setup debug messenger!\n");
    exit(EXIT_FAILURE);
  }
}

void initVulkan(VkInstance *instance, VkDebugUtilsMessengerEXT* debugMessenger) {
  createInstance(instance);
  setupDebugMessenger(instance, debugMessenger);
}

void mainloop(GLFWwindow* window) {
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }
}

void cleanup(GLFWwindow *window, VkInstance* instance, VkDebugUtilsMessengerEXT* debugMessenger) {
  if (enableValiationLayers) {
    DestroyDebugUtilsMessengerEXT(*instance, *debugMessenger, nullptr);
  }
  vkDestroyInstance(*instance, NULL);
  glfwDestroyWindow(window);
  glfwTerminate();
}

void run() {
  GLFWwindow *window = NULL;
  VkInstance instance;
  VkDebugUtilsMessengerEXT debugMessenger;
  initWindow(window);
  initVulkan(&instance, &debugMessenger);
  mainloop(window);
  cleanup(window,&instance,&debugMessenger);
}

int main() {
  try {
    run();
  } catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;

}
//56
