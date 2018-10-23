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

#include "Graph.hpp"

void Graph::computeProperties() noexcept
{
    std::vector<int> degrees;
    degrees.reserve(m_matrix.size());

    int maxDegree = 0;
    int minDegree = m_matrix.size();
    int doubleSize = 0;

    for (auto& row : m_matrix)
    {
        int degree = 0;

        for (bool val : row)
        {
            degree += static_cast<int>(val);
        }

        degrees.push_back(degree);
        maxDegree = std::max(degree, maxDegree);
        minDegree = std::min(degree, minDegree);
        doubleSize += degree;
    }

    m_degrees = degrees;
    m_maxDegree = maxDegree;
    m_minDegree = minDegree;
    m_size = doubleSize / 2;
}

Graph Graph::induced(const std::vector<int>& nodeIndices) const noexcept
{
    std::vector<std::vector<bool>> matrix;
    matrix.reserve(nodeIndices.size());

    for (int i : nodeIndices)
    {
        std::vector<bool> row;
        row.reserve(nodeIndices.size());

        for (int j : nodeIndices)
        {
            row.push_back(m_matrix[i][j]);
        }

        matrix.push_back(row);
    }

    return Graph(matrix);
}

std::vector<int> Graph::getNodeNeighbours(int index) const noexcept
{
    std::vector<int> neighbours;
    neighbours.reserve(getNodeDegree(index));

    for (int i = 0; i < getDegree(); i++)
    {
        if (m_matrix[index][i])
        {
            neighbours.push_back(i);
        }
    }

    return neighbours;
}
