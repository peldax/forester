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

#include "Graph.hpp"

class MutableGraph : public Graph
{
    /**
     * Adds new edge between given nodes
     * @param index1
     * @param index2
     */
    void addEdge(int index1, int index2) noexcept;

    /**
     * Removes edge between given nodes
     * @param index1
     * @param index2
     */
    void removeEdge(int index1, int index2) noexcept;

    /**
     * Adds new node with zero edges
     */
    void addNode() noexcept;

    /**
     * Removes node at given index
     */
    void removeNode(int index) noexcept;
};
