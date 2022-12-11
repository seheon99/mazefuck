/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mazegen.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyu <seyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 01:46:39 by seyu              #+#    #+#             */
/*   Updated: 2020/06/25 10:35:48 by seyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAZEGEN_HPP
#define MAZEGEN_HPP

#include <string>

enum e_dir { UP, RIGHT, DOWN, LEFT };
typedef enum e_dir t_dir;

class Mazegen {
  private:
    char start_char;
    char end_char;
    char wall_char;
    char blank_char;
    bool is_surrounded(size_t x, size_t y);
    void new_xline(size_t y);
    void new_yline(size_t x);
    void extend_left();
    void extend_right();
    void extend_top();
    void extend_bottom();
    void extend_in();
    void make_road(size_t &x, size_t &y, const t_dir direction, bool end);

  public:
    Mazegen(const std::string set, std::string binary);
    ~Mazegen();
    char **map;
    size_t mapsize_x;
    size_t mapsize_y;
};

#endif
