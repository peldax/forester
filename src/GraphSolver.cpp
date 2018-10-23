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

#include <algorithm>
#include <cmath>
#include "GraphSolver.hpp"
#include "Graph.hpp"
#include "MutableGraph.hpp"

bool GraphSolver::isContinuous() const noexcept
{
    return bfContinuity();
}

bool GraphSolver::isLocallyContinuous() const noexcept
{
    return chartrandPippert1974() || bfLocalContinuity();
}

int GraphSolver::getNodeContinuity() const noexcept
{
    return bfNodeContinuity();
}

int GraphSolver::getEdgeContinuity() const noexcept
{
    return bfEdgeContinuity();
}

bool GraphSolver::isKNodeContinuous(int k) const noexcept
{
    return getNodeContinuity() >= k;
}

bool GraphSolver::isKEdgeContinuous(int k) const noexcept
{
    return getEdgeContinuity() >= k;
}

int GraphSolver::getCircumference() noexcept
{
    return bfCircumference();
}

bool GraphSolver::hasClaw() noexcept
{
    return bfHasClaw();
}

bool GraphSolver::isClaw() noexcept
{
    if (m_graph->getDegree() != 4)
    {
        return false;
    }

    int count3 = 0;
    int count1 = 0;

    for (int i = 0; i < m_graph->getDegree(); i++)
    {
        int degree = m_graph->getNodeDegree(i);

        if (degree == 3)
        {
            count3++;
        }
        else if (degree == 1)
        {
            count1++;
        }
        else
        {
            return false;
        }
    }

    return count3 == 1 && count1 == 3;
}

bool GraphSolver::isComplete() noexcept
{
    for (int degree : m_graph->getDegrees())
    {
        if (degree != m_graph->getDegree() - 1)
        {
            return false;
        }
    }

    return true;
}

bool GraphSolver::hasHamiltonRoute() noexcept
{
    return bfHamiltonRoute();
}

bool GraphSolver::hasHamiltonCircle() noexcept
{
    return dirac1952() || ore1960() || poza1963() || chvatal1972() || bondyChvatal1974() || oberlySummer1979() || bfHamiltonCircle();
}

bool GraphSolver::chartrandPippert1974() const noexcept
{
    if (m_graph->getMinDegree() > std::floor((2.0 / 3) * (m_graph->getDegree() - 1)))
    {
        return true;
    }

    for (int i = 0; i < m_graph->getDegree(); i++)
    {
        for (int j = i; j < m_graph->getDegree(); j++)
        {
            if (i == j)
            {
                continue;
            }

            if (!m_graph->hasEdge(i, j) &&
                    m_graph->getNodeDegree(i) + m_graph->getNodeDegree(j) <= std::ceil((4.0 / 3.0) * (m_graph->getDegree() - 1)))
            {
                return false;
            }
        }
    }

    return true;
}

bool GraphSolver::dirac1952() const noexcept
{
    if (m_graph->getDegree() < 3)
    {
        return false;
    }

    return m_graph->getMinDegree() >= std::ceil(m_graph->getDegree() / 2.0);
}

bool GraphSolver::ore1960() const noexcept
{
    for (int i = 0; i < m_graph->getDegree(); i++)
    {
        for (int j = i; j < m_graph->getDegree(); j++)
        {
            if (i == j)
            {
                continue;
            }

            if (!m_graph->hasEdge(i, j) &&
                    m_graph->getNodeDegree(i) + m_graph->getNodeDegree(j) < m_graph->getDegree())
            {
                return false;
            }
        }
    }

    return false;
}

bool GraphSolver::poza1963() const noexcept
{
    if (m_graph->getDegree() < 3)
    {
        return false;
    }

    for (int i  = 1; i <= std::floor(m_graph->getDegree() / 2.0); i++)
    {
        int nodeCount = 0;

        for (int degree : m_graph->getDegrees())
        {
            if (degree < i)
            {
                nodeCount += 1;
            }
        }

        if (nodeCount >= i)
        {
            return false;
        }
    }

    return true;
}

bool GraphSolver::chvatal1972() const noexcept
{
    auto orderedDegree = m_graph->getDegrees();
    std::sort(orderedDegree.begin(), orderedDegree.end());

    for (int i  = 1; i <= std::floor(m_graph->getDegree() / 2.0); i++)
    {
        if (orderedDegree.at(i - 1) < i + 1 ||
            orderedDegree.at(m_graph->getDegree() - i - 1) < m_graph->getDegree() - i)
        {
            return false;
        }
    }

    return true;
}

bool GraphSolver::bondyChvatal1974() const noexcept
{
    if (m_graph->getDegree() < 3)
    {
        return false;
    }

    auto closure = MutableGraph(m_graph->getMatrix());
    bool change = true;

    while (change)
    {
        change = false;

        for (int i = 0; i < m_graph->getDegree(); i++)
        {
            for (int j = 0; j < m_graph->getDegree(); j++)
            {
                if (i == j || closure.hasEdge(i, j))
                {
                    continue;
                }

                if (closure.getNodeDegree(i) + closure.getNodeDegree(j) >= closure.getDegree())
                {
                    closure.addEdge(i, j);
                    change = true;
                    continue;
                }
            }
        }
    }

    return closure.isComplete();
}

bool GraphSolver::oberlySummer1979() noexcept
{
    return isContinuous() && isLocallyContinuous() && !hasClaw();
}

static void recursiveFn(int index, std::vector<bool>& search, const std::vector<std::vector<bool>>& matrix)
{
    search[index] = true;
    for (int i = 0; i < matrix.size(); i++)
    {
        bool val = matrix.at(index).at(i);

        if (val && search.at(i) != true)
        {
            search[i] = true;
            recursiveFn(i, search, matrix);
        }
    }
}

bool GraphSolver::bfContinuity() const noexcept
{
    std::vector<bool> search(m_graph->getDegree(), false);

    // TODO make this a lambda fn
    recursiveFn(0, search, m_graph->getMatrix());

    return std::find(search.begin(), search.end(), false) == search.end();
}

bool GraphSolver::bfLocalContinuity() const noexcept
{
    // TODO
    return false;
}

int GraphSolver::bfNodeContinuity() const noexcept
{
    // TODO
    return 0;
}

int GraphSolver::bfEdgeContinuity() const noexcept
{
    // TODO
    return 0;
}

int GraphSolver::bfCircumference() const noexcept
{
    return 0;
}

bool GraphSolver::bfHasClaw() const noexcept
{
    if (m_graph->getDegree() < 4)
    {
        return false;
    }

    if (m_graph->getDegree() == 4)
    {
        return m_graph->isClaw();
    }

    for (int i = 0; i < m_graph->getDegree(); i++)
    {
        if (m_graph->getNodeDegree(i) < 3)
        {
            continue;
        }

        auto neighbours = m_graph->getNodeNeighbours(i);

        // TODO better way to get all triplets
        for (int j = 0; j < neighbours.size() - 2; j++)
        {
            for (int k = 1; k < neighbours.size() - 1; k++)
            {
                for (int l = 2; l < neighbours.size(); l++)
                {
                    auto subgraph = m_graph->induced({i, neighbours.at(j), neighbours.at(k), neighbours.at(l)});

                    if (subgraph.isClaw())
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool GraphSolver::bfHamiltonRoute() const noexcept
{
    // TODO
    return true;
}

bool GraphSolver::bfHamiltonCircle() const noexcept
{
    // TODO
    return false;
}
