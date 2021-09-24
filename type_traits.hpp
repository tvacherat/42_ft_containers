/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 14:13:40 by tvachera          #+#    #+#             */
/*   Updated: 2021/09/07 14:15:33 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
 #define TYPE_TRAITS_HPP

namespace ft
{
	/*
		enable_if class templates below
		The type T is enabled as member type enable_if::type if Cond is true
		https://www.cplusplus.com/reference/type_traits/enable_if/?kw=enable_if
	*/
	template<bool Cond, typename T = void>
	struct enable_if {};

	template<typename T>
	struct enable_if<true, T>
	{
		typedef T	type;
	};
	/*
		integral_constant class template below
		This template is designed to provide compile-time constants as types
		https://www.cplusplus.com/reference/type_traits/integral_constant/
	*/
	template <typename T, T v>
	struct integral_constant
	{
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T,v> type;

		operator T()
		{
			return (v);
		}
	};
	/*
		is_integral class template and its specializations below
		Trait class that identifies whether T is an integral type
		https://www.cplusplus.com/reference/type_traits/is_integral/
	*/
	template<typename T>
	struct is_integral : public integral_constant<bool, false> {} ;

	template<>
	struct is_integral<bool> : public integral_constant<bool, true> {} ;

	template<>
	struct is_integral<char> : public integral_constant<bool, true> {} ;

	template<>
	struct is_integral<wchar_t> : public integral_constant<bool, true> {} ;

	template<>
	struct is_integral<signed char> : public integral_constant<bool, true> {} ;

	template<>
	struct is_integral<short int> : public integral_constant<bool, true> {} ;

	template<>
	struct is_integral<int> : public integral_constant<bool, true> {} ;

	template<>
	struct is_integral<long int> : public integral_constant<bool, true> {} ;

	template<>
	struct is_integral<long long int> : public integral_constant<bool, true> {} ;

	template<>
	struct is_integral<unsigned char> : public integral_constant<bool, true> {} ;

	template<>
	struct is_integral<unsigned short int> : public integral_constant<bool, true> {} ;

	template<>
	struct is_integral<unsigned int> : public integral_constant<bool, true> {} ;

	template<>
	struct is_integral<unsigned long int> : public integral_constant<bool, true> {} ;

	template<>
	struct is_integral<unsigned long long int> : public integral_constant<bool, true> {} ;
}

#endif