/*                                                                          */
/* Copyright (c) 2018 Václav Pelíšek (info@peldax.com)                      */
/* This file is part of Forester.                                           */
/*                                                                          */
/* Forester is free software: you can redistribute it and/or modify         */
/* it under the terms of the GNU General Public License as published by     */
/* the Free Software Foundation, either version 3 of the License, or        */
/* (at your option) any later version.                                      */
/*                                                                          */
/* Forester is distributed in the hope that it will be useful,              */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of           */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            */
/* GNU General Public License for more details.                             */
/*                                                                          */
/* You should have received a copy of the GNU General Public License        */
/* along with Forester.  If not, see <http://www.gnu.org/licenses/>.        */
/*                                                                          */

#include "MutableGraph.hpp"

void MutableGraph::addEdge(int index1, int index2) noexcept
{
    if (m_matrix.at(index1).at(index2))
    {
        return;
    }

    m_matrix[index1][index2] = true;
    m_matrix[index2][index1] = true;

    computeProperties();
}

void MutableGraph::removeEdge(int index1, int index2) noexcept
{
    if (!m_matrix.at(index1).at(index2))
    {
        return;
    }

    m_matrix[index1][index2] = false;
    m_matrix[index2][index1] = false;

    computeProperties();
}

void MutableGraph::addNode() noexcept
{
    std::vector<bool> temp;
    temp.reserve(getDegree() + 1);
    temp.push_back(false);

    for (auto& row : m_matrix)
    {
        row.push_back(false);
        temp.push_back(false);
    }

    m_matrix.push_back(temp);

    computeProperties();
}

void MutableGraph::removeNode(int index) noexcept
{
    for (int i = 0; i < getDegree(); i++)
    {
        m_matrix.at(i).erase(m_matrix.at(i).begin() + index);
    }

    m_matrix.erase(m_matrix.begin() + index);

    computeProperties();
}
