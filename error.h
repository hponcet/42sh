/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MrRobot <mimazouz@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 12:07:03 by MrRobot           #+#    #+#             */
/*   Updated: 2016/11/17 15:32:36 by MrRobot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

//# define ER_HIS "42sh: unable to open history file\n"
# define ER_PATH "42sh: Environnement variable $PATH not found\n"
//# define ER_HOME "42sh: Environnement variable $HOME not found\n"
# define ER_OFD "42sh: unable to open the terminal device file\n"
# define ER_GETENT "42sh: unable to find the terminfo database\n"
# define ER_GETATTR "42sh: unable to retrieve the terminal parameters\n"
# define ER_SETATTR "tcsetattr: unable to set the terminal parameters\n"
# define ER_MEM "malloc: memory allocation has failed\n"
# define ER_READ "read: an error occured while reading the input\n"
# define ER_TERM_C "42sh: terminal capabilities not supported\n"
# define ER_IOCTL "ioctl: unable to get the terminal state infos\n"

#endif