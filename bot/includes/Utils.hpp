/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:36:30 by sayar             #+#    #+#             */
/*   Updated: 2023/02/20 16:34:38 by sayar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <string>
# include <vector>
# include <stdexcept>
# include <sstream>

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

};


#endif