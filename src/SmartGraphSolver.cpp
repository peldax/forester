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

#include "SmartGraphSolver.hpp"

bool SmartGraphSolver::isContinuous() const noexcept
{
    if (m_continuous == CacheState::UNKNOWN)
    {
        const bool result = GraphSolver::isContinuous();
        m_continuous = result ? CacheState::TRUE : CacheState::FALSE;
    }

    return m_continuous == CacheState::TRUE;
}

bool SmartGraphSolver::isLocallyContinuous() const noexcept
{
    if (m_locallyContinuous == CacheState::UNKNOWN)
    {
        const bool result = chartrandPippert1974() || bfLocalContinuity();
        m_locallyContinuous = result ? CacheState::TRUE : CacheState::FALSE;
    }

    return m_locallyContinuous == CacheState::TRUE;
}

int SmartGraphSolver::getNodeContinuity() const noexcept
{
    if (m_nodeContinuity == -1)
    {
        if (!isContinuous())
        {
            m_nodeContinuity = 0;
            return m_nodeContinuity;
        }

        m_nodeContinuity = 1; // TODO
    }

    return m_nodeContinuity;
}

int SmartGraphSolver::getEdgeContinuity() const noexcept
{
    if (m_edgeContinuity == -1)
    {
        if (!isContinuous())
        {
            m_edgeContinuity = 0;
            return m_nodeContinuity;
        }

        m_edgeContinuity = 1; // TODO
    }

    return m_edgeContinuity;
}

bool SmartGraphSolver::isKNodeContinuous(int k) const noexcept
{
    return getNodeContinuity() >= k;
}

bool SmartGraphSolver::isKEdgeContinuous(int k) const noexcept
{
    return getEdgeContinuity() >= k;
}

int SmartGraphSolver::getCircumference() const noexcept
{
    if (m_circumference == -1)
    {
        if (m_hamiltonCircle == CacheState::TRUE)
        {
            m_circumference = GraphSolver::getCircumference();
            return m_circumference;
        }

        m_circumference = 0;// TODO
    }

    return m_circumference;
}

bool SmartGraphSolver::hasClaw() const noexcept
{
    if (m_hasClaw == CacheState::UNKNOWN)
    {
        const bool result = bfHasClaw();
        m_hasClaw = result ? CacheState::TRUE : CacheState::FALSE;
    }

    return m_hasClaw == CacheState::TRUE;
}

bool SmartGraphSolver::isClaw() const noexcept
{
    return GraphSolver::isClaw();
}

bool SmartGraphSolver::isComplete() const noexcept
{
    return GraphSolver::isComplete();
}

bool SmartGraphSolver::hasHamiltonRoute() const noexcept
{
    if (m_hamiltonRoute == CacheState::UNKNOWN)
    {
        if (m_hamiltonCircle == CacheState::TRUE)
        {
            m_hamiltonRoute = CacheState::TRUE;
            return true;
        }

        const bool result = GraphSolver::hasHamiltonRoute();
        m_hamiltonRoute = result ? CacheState::TRUE : CacheState::FALSE;
    }

    return m_hamiltonRoute == CacheState::TRUE;
}

bool SmartGraphSolver::hasHamiltonCircle() const noexcept
{
    if (m_hamiltonRoute == CacheState::UNKNOWN)
    {
        if (m_hamiltonRoute == CacheState::FALSE)
        {
            m_hamiltonRoute = CacheState::FALSE;
            return false;
        }

        const bool result = GraphSolver::hasHamiltonCircle();
        m_hamiltonRoute = result ? CacheState::TRUE : CacheState::FALSE;
    }

    return m_hamiltonRoute == CacheState::TRUE;
}

int SmartGraphSolver::getChromaticNumber() const noexcept
{
    return 0;
}
