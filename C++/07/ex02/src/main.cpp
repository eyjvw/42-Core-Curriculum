/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 07:42:23 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/29 21:35:40 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Array.hpp"
#include <iostream>
#include <string>

// Color codes for output
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define RESET "\033[0m"

void test_default_constructor()
{
	std::cout << YELLOW << "=== Test: Default Constructor ===" << RESET << std::endl;
	Array<int> arr;
	std::cout << "Size of default array: " << arr.size() << std::endl;
	if (arr.size() == 0)
		std::cout << GREEN << "✓ PASS" << RESET << std::endl;
	else
		std::cout << RED << "✗ FAIL" << RESET << std::endl;
	std::cout << std::endl;
}

void test_parameterized_constructor()
{
	std::cout << YELLOW << "=== Test: Parameterized Constructor ===" << RESET << std::endl;
	Array<int> arr(5);
	std::cout << "Size of array(5): " << arr.size() << std::endl;
	if (arr.size() == 5)
		std::cout << GREEN << "✓ PASS" << RESET << std::endl;
	else
		std::cout << RED << "✗ FAIL" << RESET << std::endl;
	std::cout << std::endl;
}

void test_initialization()
{
	std::cout << YELLOW << "=== Test: Array Initialization ===" << RESET << std::endl;
	Array<int> arr(3);
	arr[0] = 10;
	arr[1] = 20;
	arr[2] = 30;
	
	if (arr[0] == 10 && arr[1] == 20 && arr[2] == 30)
		std::cout << GREEN << "✓ PASS - Values correctly initialized" << RESET << std::endl;
	else
		std::cout << RED << "✗ FAIL - Values not correctly set" << RESET << std::endl;
	std::cout << std::endl;
}

void test_copy_constructor()
{
	std::cout << YELLOW << "=== Test: Copy Constructor ===" << RESET << std::endl;
	Array<int> arr1(4);
	arr1[0] = 100;
	arr1[1] = 200;
	arr1[2] = 300;
	arr1[3] = 400;
	
	Array<int> arr2(arr1);
	
	std::cout << "Original: [" << arr1[0] << ", " << arr1[1] << ", " 
			  << arr1[2] << ", " << arr1[3] << "]" << std::endl;
	std::cout << "Copy:     [" << arr2[0] << ", " << arr2[1] << ", " 
			  << arr2[2] << ", " << arr2[3] << "]" << std::endl;
	
	if (arr2[0] == 100 && arr2[1] == 200 && arr2[2] == 300 && arr2[3] == 400)
		std::cout << GREEN << "✓ PASS - Deep copy successful" << RESET << std::endl;
	else
		std::cout << RED << "✗ FAIL - Deep copy failed" << RESET << std::endl;
	std::cout << std::endl;
}

void test_deep_copy()
{
	std::cout << YELLOW << "=== Test: Deep Copy (Modification Independence) ===" << RESET << std::endl;
	Array<int> arr1(3);
	arr1[0] = 1;
	arr1[1] = 2;
	arr1[2] = 3;
	
	Array<int> arr2(arr1);
	arr2[0] = 999;
	
	std::cout << "Original after copy modification: " << arr1[0] << std::endl;
	std::cout << "Copy after modification: " << arr2[0] << std::endl;
	
	if (arr1[0] == 1 && arr2[0] == 999)
		std::cout << GREEN << "✓ PASS - Deep copy confirmed (independent)" << RESET << std::endl;
	else
		std::cout << RED << "✗ FAIL - Not a deep copy" << RESET << std::endl;
	std::cout << std::endl;
}

void test_assignment_operator()
{
	std::cout << YELLOW << "=== Test: Assignment Operator ===" << RESET << std::endl;
	Array<int> arr1(3);
	arr1[0] = 11;
	arr1[1] = 22;
	arr1[2] = 33;
	
	Array<int> arr2(5);
	arr2 = arr1;
	
	std::cout << "Size after assignment: " << arr2.size() << std::endl;
	std::cout << "Values: [" << arr2[0] << ", " << arr2[1] << ", " << arr2[2] << "]" << std::endl;
	
	if (arr2.size() == 3 && arr2[0] == 11 && arr2[1] == 22 && arr2[2] == 33)
		std::cout << GREEN << "✓ PASS - Assignment successful" << RESET << std::endl;
	else
		std::cout << RED << "✗ FAIL - Assignment failed" << RESET << std::endl;
	std::cout << std::endl;
}

void test_self_assignment()
{
	std::cout << YELLOW << "=== Test: Self Assignment ===" << RESET << std::endl;
	Array<int> arr(2);
	arr[0] = 42;
	arr[1] = 84;
	
	Array<int> &ref = arr;
	arr = ref;  // Self assignment
	
	if (arr.size() == 2 && arr[0] == 42 && arr[1] == 84)
		std::cout << GREEN << "✓ PASS - Self assignment handled correctly" << RESET << std::endl;
	else
		std::cout << RED << "✗ FAIL - Self assignment corrupted array" << RESET << std::endl;
	std::cout << std::endl;
}

void test_index_out_of_bounds_negative()
{
	std::cout << YELLOW << "=== Test: Negative Index (Out of Bounds) ===" << RESET << std::endl;
	Array<int> arr(3);
	arr[0] = 10;
	
	try
	{
		(void)arr[-1];
		std::cout << RED << "✗ FAIL - Exception not thrown" << RESET << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
		std::cout << GREEN << "✓ PASS - Exception correctly thrown" << RESET << std::endl;
	}
	std::cout << std::endl;
}

void test_index_out_of_bounds_positive()
{
	std::cout << YELLOW << "=== Test: Index Beyond Size (Out of Bounds) ===" << RESET << std::endl;
	Array<int> arr(3);
	
	try
	{
		(void)arr[5];
		std::cout << RED << "✗ FAIL - Exception not thrown" << RESET << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
		std::cout << GREEN << "✓ PASS - Exception correctly thrown" << RESET << std::endl;
	}
	std::cout << std::endl;
}

void test_boundary_access()
{
	std::cout << YELLOW << "=== Test: Boundary Access ===" << RESET << std::endl;
	Array<int> arr(5);
	
	try
	{
		arr[0] = 1;      // First element
		arr[4] = 5;      // Last element
		
		int first = arr[0];
		int last = arr[4];
		
		if (first == 1 && last == 5)
			std::cout << GREEN << "✓ PASS - Boundary access successful" << RESET << std::endl;
		else
			std::cout << RED << "✗ FAIL - Boundary access failed" << RESET << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << RED << "✗ FAIL - Exception thrown: " << e.what() << RESET << std::endl;
	}
	std::cout << std::endl;
}

void test_different_types()
{
	std::cout << YELLOW << "=== Test: Different Data Types ===" << RESET << std::endl;
	
	// Test with float
	Array<float> floatArr(2);
	floatArr[0] = 3.14f;
	floatArr[1] = 2.71f;
	
	// Test with string
	Array<std::string> stringArr(3);
	stringArr[0] = "Hello";
	stringArr[1] = "World";
	stringArr[2] = "Test";
	
	std::cout << "Float array: [" << floatArr[0] << ", " << floatArr[1] << "]" << std::endl;
	std::cout << "String array: [" << stringArr[0] << ", " << stringArr[1] << ", " 
			  << stringArr[2] << "]" << std::endl;
	
	if (floatArr[0] > 3.13f && floatArr[1] > 2.70f &&
		stringArr[0] == "Hello" && stringArr[1] == "World")
		std::cout << GREEN << "✓ PASS - Template works with different types" << RESET << std::endl;
	else
		std::cout << RED << "✗ FAIL - Template type handling failed" << RESET << std::endl;
	std::cout << std::endl;
}

void test_large_array()
{
	std::cout << YELLOW << "=== Test: Large Array ===" << RESET << std::endl;
	Array<int> arr(10000);
	
	// Fill with values
	for (int i = 0; i < 10000; i++)
		arr[i] = i;
	
	// Verify
	bool valid = true;
	for (int i = 0; i < 10000; i++)
	{
		if (arr[i] != i)
		{
			valid = false;
			break;
		}
	}
	
	if (valid)
		std::cout << GREEN << "✓ PASS - Large array handling successful" << RESET << std::endl;
	else
		std::cout << RED << "✗ FAIL - Large array handling failed" << RESET << std::endl;
	std::cout << std::endl;
}

void test_const_access()
{
	std::cout << YELLOW << "=== Test: Const Array Access ===" << RESET << std::endl;
	const Array<int> arr(3);
	
	// This should work with the const operator[]
	try
	{
		// We can't modify, but we can read
		// Since the array was just created, values are default-initialized
		(void)arr[0];
		std::cout << GREEN << "✓ PASS - Const access works" << RESET << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << RED << "✗ FAIL - Const access failed: " << e.what() << RESET << std::endl;
	}
	std::cout << std::endl;
}

void test_const_out_of_bounds()
{
	std::cout << YELLOW << "=== Test: Const Access Out of Bounds ===" << RESET << std::endl;
	const Array<int> arr(2);
	
	try
	{
		(void)arr[10];
		std::cout << RED << "✗ FAIL - Exception not thrown" << RESET << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
		std::cout << GREEN << "✓ PASS - Const out of bounds handled" << RESET << std::endl;
	}
	std::cout << std::endl;
}

int main(void)
{
	std::cout << GREEN << "████████████████████████████████████" << RESET << std::endl;
	std::cout << GREEN << "  ARRAY TEMPLATE CLASS - TEST SUITE" << RESET << std::endl;
	std::cout << GREEN << "████████████████████████████████████" << RESET << std::endl;
	std::cout << std::endl;
	
	test_default_constructor();
	test_parameterized_constructor();
	test_initialization();
	test_copy_constructor();
	test_deep_copy();
	test_assignment_operator();
	test_self_assignment();
	test_index_out_of_bounds_negative();
	test_index_out_of_bounds_positive();
	test_boundary_access();
	test_different_types();
	test_large_array();
	test_const_access();
	test_const_out_of_bounds();
	
	std::cout << GREEN << "████████████████████████████████████" << RESET << std::endl;
	std::cout << GREEN << "     TEST SUITE COMPLETE" << RESET << std::endl;
	std::cout << GREEN << "████████████████████████████████████" << RESET << std::endl;
	
	return (0);
}
