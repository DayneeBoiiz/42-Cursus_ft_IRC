/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:36:30 by sayar             #+#    #+#             */
/*   Updated: 2023/02/20 18:47:54 by sayar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <string>
# include <vector>
# include <stdexcept>
# include <sstream>
# include <memory>

namespace ft {

	typedef std::vector<std::string>	s_vector;

	static inline s_vector split(std::string const &message) {

		std::string			buffer;
		std::stringstream	ss(message);
		s_vector			args;

		while (ss >> buffer) {
			args.push_back(buffer);
		}

		return (args);

	}

	static inline std::string	join(std::string const &separtor, s_vector &vector) {
		std::string str;
		for (auto it = vector.begin(); it != vector.end(); it++) {
			str.append(*it).append(it + 1 == vector.end() ? "" : separtor);
		}
		return (str);
	}

	template<typename ... Args>
	std::string formatString(std::string const &format, Args ... args) {

		int size_s = std::snprintf(NULL, 0, format.c_str(), args ...) + 1;
		if (size_s <= 0) {
			throw std::runtime_error("Error while formating...");
		}
		auto size = static_cast<size_t>(size_s);
		std::unique_ptr<char[]> buffer(new char[size]);
		std::snprintf(buffer.get(), size, format.c_str(), args ...);
		return (std::string(buffer.get(), buffer.get() + size - 1));

	}

};


#endif