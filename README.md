# 🚌 RouteMate — Transport Management System

A comprehensive, multi-role console-based C++ application for managing an entire institutional transport network — vehicles, routes, drivers, student passes, billing, and financial reporting — all from one system.

## ✨ Features

### 🔐 Multi-Role Access System
- **Admin** — full system control and user management
- **Student** — request transport passes, view assigned routes
- **Driver** — view assigned vehicle and trip details
- **Finance Manager** — clear pass payments, manage petrol logs and monthly capital
- **Transport Manager** — manage vehicles, routes, and driver assignments
- Public registration portal for new accounts across all roles

### 🚐 Fleet & Route Management
- Add and manage vehicles (buses/vans) with capacity, fuel type, and fuel efficiency
- Create routes with multiple stops and approximate distances
- Assign drivers to specific vehicles
- Track live occupied seats per vehicle

### 🎫 Digital Pass System
- Students can request transport passes for a specific route and stop
- Waitlist system when a route is full, with automatic waitlist processing
- Pass activation with issue/expiry dates and automatic expiry sweeping
- Auto-generates a downloadable **Pass PDF** on approval

### 💰 Finance & Billing
- Petrol price tracking and per-vehicle fuel cost calculation
- Monthly capital budget tracking with live status view
- Bill generation and payment record management
- Full **Financial Report (PDF)** generation
- **Excel (.xlsx) Finance Report** export, built manually via raw ZIP/XML generation — no external libraries required

### 📊 Reporting & Analytics
- Daily trip summary per vehicle
- System-wide quick stats (public-facing, no login required)
- Route waitlist viewer and processor
- Driver assignment overview

### 💾 Full Data Persistence
Every module — users, vehicles, routes, passes, bills, payments, waitlists, trip logs, petrol logs, and monthly capital — is saved to and loaded from disk, so the entire system state survives between runs.

## 🖥️ How to Run

```bash
g++ finalTransport.cpp -o RouteMate
./RouteMate
```

## 📋 Main Portal
Admin Console
Student Console
Driver Console
Finance Manager Console
Transport Manager Console
System Quick Stats (Public)
Shutdown System
Register New Account

## 🛠️ Tech Used

- **Language:** C++ (OOP with inheritance — `User` base class extended by `Admin`, `Student`, `Driver`, `FinanceManager`, `TransportManager`)
- **Concepts:** class inheritance & polymorphism, `shared_ptr` smart pointers, file I/O, input validation, manual PDF generation, manual .xlsx (ZIP/CRC32/XML) generation

## 📌 Notes

Built as an advanced C++ project simulating a real-world, multi-stakeholder transport management platform — combining OOP design, persistent storage, role-based access control, and self-contained report generation (PDF & Excel) without relying on third-party libraries.
