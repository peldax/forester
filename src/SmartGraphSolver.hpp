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

#include "CacheState.hpp"
#include "GraphSolver.hpp"

class SmartGraphSolver : public GraphSolver
{

protected:

    mutable CacheState m_continuous = CacheState::UNKNOWN;
    mutable CacheState m_locallyContinuous = CacheState::UNKNOWN;
    mutable CacheState m_hasClaw = CacheState::UNKNOWN;
    mutable CacheState m_hamiltonRoute = CacheState::UNKNOWN;
    mutable CacheState m_hamiltonCircle = CacheState::UNKNOWN;
    mutable int m_nodeContinuity = -1;
    mutable int m_edgeContinuity = -1;
    mutable int m_circumference = -1;

public:

    explicit SmartGraphSolver(Graph* graph) :
        GraphSolver(graph)
    {}


public:

    /*
     * CONTINUITY
     */

    /**
     * Returns whether graph is continuous
     * @return
     */
    bool isContinuous() const noexcept override;

    /**
     * Returns whether graph is locally continuous
     * @return
     */
    bool isLocallyContinuous() const noexcept override;

    /**
     * Returns node continuity of graph
     * @return
     */
    int getNodeContinuity() const noexcept override;

    /**
     * Returns edge continuity
     * @return
     */
    int getEdgeContinuity() const noexcept override;

    /**
     * Returns whether graph is K node continuous
     * @param k
     * @return
     */
    bool isKNodeContinuous(int k) const noexcept override;

    /**
     * Returns whether graph is K edge continuous
     * @param k
     * @return
     */
    bool isKEdgeContinuous(int k) const noexcept override;

public:

    /*
     * OTHER PROPERTIES
     */

    /**
     * Returns length of longest circle in graph
     * @return
     */
    int getCircumference() const noexcept override;

    /**
     * Returns whether graph has K13 as subgraph
     * @return
     */
    bool hasClaw() const noexcept override;

    /**
     * Returns whether graph is K13 type graph
     * @return
     */
    bool isClaw() const noexcept override;

    /**
     * Returns whether graph is complete graph
     * @return
     */
    bool isComplete() const noexcept override;

public:

    /*
     * HAMILTON PROPERTIES
     */

    /**
     * Returns whether graph contains Hemilton route
     * @return
     */
    bool hasHamiltonRoute() const noexcept override;

    /**
     * Returns whether graph contains Hemilton circle
     * @return
     */
    bool hasHamiltonCircle() const noexcept override;

public:

    /*
     * COLORING
     */

    /**
     * Returns graphs minimal coloring
     * @return
     */
    int getMinColoring() const noexcept override;
};
