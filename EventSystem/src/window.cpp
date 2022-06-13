#include <iostream>
#include "window.h"
#include "mouseevent.h"
#include "keyboardevent.h"
#include "windowevent.h"

namespace Core
{
	Window::Window(const std::string& name, int width, int height)
	{
		init(name, width, height);
		

		setfnCallback([this](Event& e)
			{
				if (e.getType() == Event::EventType::WINDOW_CLOSED_EVENT)
				{
					glfwSetWindowShouldClose(window, GL_TRUE);
				}
				std::cout << e.format() << std::endl;
			});
	}

	void Window::init(const std::string& name, int width, int height)
	{
		this->name = name;
		this->width = width;
		this->height = height;

		if (!glfwInit())
		{
			_asm {
				int 3
			}
		}

		window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

		if (!window)
		{
			_asm {
				int 3
			}
		}

		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, this);
		glfwSetCursorPosCallback(window, mouseMovedCallback);
		glfwSetScrollCallback(window, mouseScrolledCallback);
		glfwSetMouseButtonCallback(window, mouseButtonCallback);
		glfwSetKeyCallback(window, keyCallback);
		glfwSetWindowSizeCallback(window, windowResizedCallback);
		glfwSetWindowCloseCallback(window, windowClosedCallback);
	}


	void Window::mouseMovedCallback(GLFWwindow* window, double x, double y)
	{
		auto& handle = *(Window*)glfwGetWindowUserPointer(window);
		MouseMovedEvent e(x, y);
		handle.fnCallback(e);
	}

	void Window::mouseScrolledCallback(GLFWwindow* window, double x, double y)
	{
		auto& handle = *(Window*)glfwGetWindowUserPointer(window);
		MouseScrolledEvent e(y);
		handle.fnCallback(e);
	}

	void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mode)
	{
		auto& handle = *(Window*)glfwGetWindowUserPointer(window);
		if (action == GLFW_PRESS)
		{
			MouseButtonPressed e(button);
			handle.fnCallback(e);
		}
		else
		{
			MouseButtonReleased e(button);
			handle.fnCallback(e);
		}
	}

	void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		auto& handle = *(Window*)glfwGetWindowUserPointer(window);
		if (action == GLFW_PRESS)
		{
			KeyPressedEvent e(key);
			handle.fnCallback(e);
		}
		else
		{
			KeyReleasedEvent e(key);
			handle.fnCallback(e);
		}
		
	}
	
	void Window::windowResizedCallback(GLFWwindow* window, int width, int height)
	{
		auto& handle = *(Window*)glfwGetWindowUserPointer(window);
		WindowResizedEvent e(width, height);
		handle.width = width;
		handle.height = height;
		handle.fnCallback(e);
	}

	void Window::windowClosedCallback(GLFWwindow* window)
	{
		auto& handle = *(Window*)glfwGetWindowUserPointer(window);
		WindowClosedEvent e;
		handle.fnCallback(e);
	}

	Window::~Window()
	{
		glfwWindowShouldClose(window);
	}
}