/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 00:16:14 by aohssine          #+#    #+#             */
/*   Updated: 2024/09/05 00:16:21 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int     ft_strcmp(char *s1, char *s2)
{
        int     i;
        int     res;

        res = 0;
        i = 0;
        while (s1[i] || s2[i])
        {
                if (s1[i] > s2[i])
                {
                        res = s1[i] - s2[i];
                        return (res);
                }
                else if (s1[i] < s2[i])
                {
                        res = s1[i] - s2[i];
                        return (res);
                }
                i++;
        }
        return (res);
}