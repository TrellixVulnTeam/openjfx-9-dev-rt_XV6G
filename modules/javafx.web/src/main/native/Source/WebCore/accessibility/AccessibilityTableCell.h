/*
 * Copyright (C) 2008 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of Apple Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef AccessibilityTableCell_h
#define AccessibilityTableCell_h

#include "AccessibilityRenderObject.h"

namespace WebCore {

class AccessibilityTable;
class AccessibilityTableRow;

class AccessibilityTableCell : public AccessibilityRenderObject {
public:
    static Ref<AccessibilityTableCell> create(RenderObject*);
    virtual ~AccessibilityTableCell();

    virtual bool isTableCell() const override final;
    bool isTableHeaderCell() const;
    bool isColumnHeaderCell() const;
    bool isRowHeaderCell() const;

    // fills in the start location and row span of cell
    virtual void rowIndexRange(std::pair<unsigned, unsigned>& rowRange) const;
    // fills in the start location and column span of cell
    virtual void columnIndexRange(std::pair<unsigned, unsigned>& columnRange) const;

    void columnHeaders(AccessibilityChildrenVector&);
    void rowHeaders(AccessibilityChildrenVector&);

    int ariaColumnIndex() const;
    int ariaRowIndex() const;
    unsigned ariaColumnSpan() const;
    unsigned ariaRowSpan() const;
    void setARIAColIndexFromRow(int index) { m_ariaColIndexFromRow = index; }

protected:
    explicit AccessibilityTableCell(RenderObject*);

    AccessibilityTableRow* parentRow() const;
    virtual AccessibilityTable* parentTable() const;
    virtual AccessibilityRole determineAccessibilityRole() override final;

    int m_rowIndex;
    int m_ariaColIndexFromRow;

private:
    // If a table cell is not exposed as a table cell, a TH element can serve as its title UI element.
    virtual AccessibilityObject* titleUIElement() const override final;
    virtual bool exposesTitleUIElement() const override final { return true; }
    virtual bool computeAccessibilityIsIgnored() const override final;
    virtual String expandedTextValue() const override final;
    virtual bool supportsExpandedTextValue() const override final;

    bool isTableCellInSameRowGroup(AccessibilityTableCell*);
    bool isTableCellInSameColGroup(AccessibilityTableCell*);
};

} // namespace WebCore

SPECIALIZE_TYPE_TRAITS_ACCESSIBILITY(AccessibilityTableCell, isTableCell())

#endif // AccessibilityTableCell_h
