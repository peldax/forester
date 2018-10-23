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

// FORWARD DECLARATION
class Graph;

class GraphSolver
{

protected:

    Graph* m_graph;

public:

    explicit GraphSolver(Graph* graph) :
        m_graph(graph)
    {}

public:

    /**
     * Returns whether graph is continuous
     * @return
     */
    virtual bool isContinuous() const noexcept;

    /**
     * Returns whether graph is locally continuous
     * @return
     */
    virtual bool isLocallyContinuous() const noexcept;

    /**
     * Returns node continuity of graph
     * @return
     */
    virtual int getNodeContinuity() const noexcept;

    /**
     * Returns edge continuity
     * @return
     */
    virtual int getEdgeContinuity() const noexcept;

    /**
     * Returns whether graph is K node continuous
     * @param k
     * @return
     */
    virtual bool isKNodeContinuous(int k) const noexcept;

    /**
     * Returns whether graph is K edge continuous
     * @param k
     * @return
     */
    virtual bool isKEdgeContinuous(int k) const noexcept;

public:

    /*
     * OTHER PROPERTIES
     */

    /**
     * Returns length of longest circle in graph
     * @return
     */
    virtual int getCircumference() const noexcept;

    /**
     * Returns whether graph has K13 as subgraph
     * @return
     */
    virtual bool hasClaw() const noexcept;

    /**
     * Returns whether graph is K13 type graph
     * @return
     */
    virtual bool isClaw() const noexcept;

    /**
     * Returns whether graph is complete graph
     * @return
     */
    virtual bool isComplete() const noexcept;

public:

    /*
     * HAMILTON PROPERTIES
     */

    /**
     * Returns whether graph contains Hemilton route
     * @return
     */
    virtual bool hasHamiltonRoute() const noexcept;

    /**
     * Returns whether graph contains Hemilton circle
     * @return
     */
    virtual bool hasHamiltonCircle() const noexcept;

public:

    /*
     * COLORING
     */

    /**
     * Returns graphs minimal coloring
     * @return
     */
    virtual int getMinColoring() const noexcept;

protected:

    /**
     * Chartrand-Pippert (1974)
     * Local continuity
     * @return
     */
    bool chartrandPippert1974() const noexcept;

    /**
     * Dirac (1952)
     * Existence of Hamilton circle
     * @return
     */
    bool dirac1952() const noexcept;

    /**
     * Ore (1960)
     * Existence of Hamilton circle
     * @return
     */
    bool ore1960() const noexcept;

    /**
     * Póza (1963)
     * Existence of Hamilton circle
     * @return
     */
    bool poza1963() const noexcept;

    /**
     * Chvátal (1972)
     * Existence of Hamilton circle
     * @return
     */
    bool chvatal1972() const noexcept;

    /**
     * Bondy-Chvátal (1974)
     * Existence of Hamilton circle
     * @return
     */
    bool bondyChvatal1974() const noexcept;

    /**
     * Oberly-Summer (1979)
     * Existence of Hamilton circle
     * @return
     */
    bool oberlySummer1979() const noexcept;

protected:

    /*
     * Brute force checks
     */

    /**
     * Brute force check for continuity
     * @return
     */
    bool bfContinuity() const noexcept;

    /**
     * Bruce force check for local continuity
     * @return
     */
    bool bfLocalContinuity() const noexcept;

    /**
     * Bruce force calculation of degree of node continuity
     * @return
     */
    int bfNodeContinuity() const noexcept;

    /**
     * Bruce force calculation of degree of edge continuity
     * @return
     */
    int bfEdgeContinuity() const noexcept;

    /**
     * Bruce force calculation of circumeference
     * @return
     */
    int bfCircumference() const noexcept;

    /**
     * Brute force check for claw subgraph
     * @return
     */
    bool bfHasClaw() const noexcept;

    /**
     * Brute force check for Hamilton circle
     * @return
     */
    bool bfHamiltonRoute() const noexcept;

    /**
     * Brute force check for Hamilton circle
     * @return
     */
    bool bfHamiltonCircle() const noexcept;
};
