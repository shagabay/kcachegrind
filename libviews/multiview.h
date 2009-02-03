/* This file is part of KCachegrind.
   Copyright (C) 2003 Josef Weidendorfer <Josef.Weidendorfer@gmx.de>

   KCachegrind is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation, version 2.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

/*
 * MultiView, enclosing multiple (default: 2) TabView's with a user
 * choosable active view (i.e. focus). This is a splitter itself.
 * Selection of the active view is shown in the next to the right view
 * (with wrap around).
 */

#ifndef MULTIVIEW_H
#define MULTIVIEW_H

#include <qsplitter.h>
#include <q3ptrlist.h>
#include "traceitemview.h"
#include "tabview.h" // because of QPtrList<TabView>

class MultiView : public QSplitter, public TraceItemView
{
  Q_OBJECT

public:
  explicit MultiView(TopLevelBase* top, QWidget* parent = 0);

  QWidget* widget() { return this; }
  TabView* activeTabView() const { return _active; }
  void setData(TraceData*);

  void appendView();
  void removeView();
  void setChildCount(int);
  int childCount() { return _views.count(); }

  void selected(TraceItemView*, ProfileCost*);
  void activated(TraceItemView*, ProfileCost*);

  void saveLayout(const QString& prefix, const QString& postfix);
  void restoreLayout(const QString& prefix, const QString& postfix);
  void saveOptions(const QString& prefix, const QString& postfix);
  void restoreOptions(const QString& prefix, const QString& postfix);

public slots:
    void tabActivated(TabView*);

 private:
  void doUpdate(int);

  TabView* _active;
  Q3PtrList<TabView> _views;
};

#endif