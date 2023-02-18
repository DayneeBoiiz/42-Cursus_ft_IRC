/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayar <sayar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:49:22 by sayar             #+#    #+#             */
/*   Updated: 2023/02/18 12:22:21 by sayar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/Utils.hpp"

void	ft_print_log(const std::string &log) {
	time_t  raw;
    struct tm *time_info;
    char buff[80];

    time(&raw);
    time_info = localtime(&raw);

    strftime(buff, sizeof(buff), "%d-%m-%Y %H-%M-%S", time_info);
    std::string str(buff);

    std::cout << "[" << str << "]" << " " << log << std::endl;
}