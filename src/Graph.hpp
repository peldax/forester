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
 
#pragma once

#include <vector>
#include <memory>
#include "GraphSolver.hpp"
#include "SmartGraphSolver.hpp"

class Graph
{

protected:

    std::unique_ptr<GraphSolver> m_solver;

    std::vector<std::vector<bool>> m_matrix;
    std::vector<int> m_degrees;
    int m_maxDegree;
    int m_minDegree;
    int m_size;

    /**
     * Initializing function
     */
    void computeProperties() noexcept;

public:

    explicit Graph(std::vector<std::vector<bool>> matrix) :
        m_solver(std::make_unique<SmartGraphSolver>(this)),
        m_matrix(std::move(matrix))
    {
        computeProperties();
    }

    /**
     * Generates new Graph instance representing subgraph induced by selected nodes
     * @param nodeIndices
     * @return
     */
    Graph induced(const std::vector<int>& nodeIndices) const noexcept;

public:

    /**
     * Returns graphs degree (number of nodes)
     * @return
     */
    inline int getDegree() const noexcept
    {
        return m_matrix.size();
    }

    /**
     * Returns graphs size (number of edges)
     * @return
     */
    inline int getSize() const noexcept
    {
        return m_size;
    }

    /**
     * Returns whether exists edge between nodes at given indices
     * @param index1
     * @param index2
     * @return
     */
    inline bool hasEdge(int index1, int index2) const noexcept
    {
        return m_matrix.at(index1).at(index2);
    }

public:

    /**
     * Returns max node degree
     * @return
     */
    inline int getMaxDegree() const noexcept
    {
        return m_maxDegree;
    }

    /**
     * Returns min node degree
     * @return
     */
    inline int getMinDegree() const noexcept
    {
        return m_minDegree;
    }

    /**
     * Returns degree of node at given index
     * @param index
     * @return
     */
    inline int getNodeDegree(int index) const noexcept
    {
        return m_degrees.at(index);
    }

    /**
     * Returns indexes of neighbours of node at given index
     * @param index
     * @return
     */
    std::vector<int> getNodeNeighbours(int index) const noexcept;

public:

    /**
     * Returns whether graph is continuous
     * @return
     */
    bool isContinuous() const noexcept
    {
        return m_solver->isContinuous();
    }

    /**
     * Returns whether graph is locally continuous
     * @return
     */
    bool isLocallyContinuous() const noexcept
    {
        return m_solver->isLocallyContinuous();
    }

    /**
     * Returns node continuity of graph
     * @return
     */
    int getNodeContinuity() const noexcept
    {
        return m_solver->getNodeContinuity();
    }

    /**
     * Returns edge continuity
     * @return
     */
    int getEdgeContinuity() const noexcept
    {
        return m_solver->getEdgeContinuity();
    }

    /**
     * Returns whether graph is K node continuous
     * @param k
     * @return
     */
    bool isKNodeContinuous(int k) const noexcept
    {
        return m_solver->isKNodeContinuous(k);
    }

    /**
     * Returns whether graph is K edge continuous
     * @param k
     * @return
     */
    bool isKEdgeContinuous(int k) const noexcept
    {
        return m_solver->isKEdgeContinuous(k);
    }

public:

    /*
     * OTHER PROPERTIES
     */

    /**
     * Returns length of longest circle in graph
     * @return
     */
    int getCircumference() const noexcept
    {
        return m_solver->getCircumference();
    }

    /**
     * Returns whether graph has K13 as subgraph
     * @return
     */
    bool hasClaw() const noexcept
    {
        return m_solver->hasClaw();
    }

    /**
     * Returns whether graph is K13 type graph
     * @return
     */
    bool isClaw() const noexcept
    {
        return m_solver->isClaw();
    }

    /**
     * Returns whether graph is complete graph
     * @return
     */
    bool isComplete() const noexcept
    {
        return m_solver->isComplete();
    }

public:

    /*
     * HAMILTON PROPERTIES
     */

    /**
     * Returns whether graph contains Hemilton route
     * @return
     */
    bool hasHamiltonRoute() const noexcept
    {
        return m_solver->hasHamiltonRoute();
    }

    /**
     * Returns whether graph contains Hemilton circle
     * @return
     */
    bool hasHamiltonCircle() const noexcept
    {
        return m_solver->hasHamiltonCircle();
    }

public:

    /*
     * COLORING
     */

    /**
     * Returns graphs minimal coloring
     * @return
     */
    int getMinColoring() const noexcept
    {
        return m_solver->getMinColoring();
    }
};
