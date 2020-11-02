/*
Navicat SQLite Data Transfer

Source Server         : rumaburger
Source Server Version : 30714
Source Host           : :0

Target Server Type    : SQLite
Target Server Version : 30714
File Encoding         : 65001

Date: 2020-10-06 19:45:22
*/

PRAGMA foreign_keys = OFF;

-- ----------------------------
-- Table structure for centralStorage
-- ----------------------------
DROP TABLE IF EXISTS centralStorage;
CREATE TABLE centralStorage (
  id INTEGER NOT NULL,
  amount REAL NOT NULL DEFAULT 0,
  PRIMARY KEY (id),
  CONSTRAINT productID FOREIGN KEY (id) REFERENCES product (id) ON DELETE NO ACTION ON UPDATE NO ACTION
);

-- ----------------------------
-- Table structure for centralStorageTransaction
-- ----------------------------
DROP TABLE IF EXISTS centralStorageTransaction;
CREATE TABLE centralStorageTransaction (
id  INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
type  INTEGER NOT NULL,
amount  REAL NOT NULL DEFAULT 0,
idProduct  INTEGER NOT NULL,
date  TEXT NOT NULL,
idUser  INTEGER NOT NULL,
price  REAL NOT NULL DEFAULT 0,
merma  REAL DEFAULT 0,
aviable_in_local  REAL DEFAULT 0,
aviable_in_central  REAL DEFAULT 0,
CONSTRAINT productID FOREIGN KEY (idProduct) REFERENCES product (id),
CONSTRAINT userID FOREIGN KEY (idUser) REFERENCES users (id)
);

-- ----------------------------
-- Table structure for dish
-- ----------------------------
DROP TABLE IF EXISTS dish;
CREATE TABLE dish (
  id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  dishName TEXT NOT NULL,
  description TEXT,
  price REAL NOT NULL DEFAULT 0
);

-- ----------------------------
-- Table structure for dishVersions
-- ----------------------------
DROP TABLE IF EXISTS dishVersions;
CREATE TABLE dishVersions (
id  INTEGER NOT NULL,
dishName  TEXT NOT NULL,
description  TEXT,
price  REAL NOT NULL DEFAULT 0,
PRIMARY KEY (id)
);

-- ----------------------------
-- Table structure for expenses
-- ----------------------------
DROP TABLE IF EXISTS expenses;
CREATE TABLE expenses (
id  INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
description  TEXT,
price  REAL NOT NULL DEFAULT 0,
date  TEXT NOT NULL
);

-- ----------------------------
-- Table structure for ingredients
-- ----------------------------
DROP TABLE IF EXISTS ingredients;
CREATE TABLE ingredients (
  idDish INTEGER NOT NULL,
  idProduct INTEGER NOT NULL,
  amount REAL NOT NULL DEFAULT 0,
  PRIMARY KEY (idDish, idProduct),
  CONSTRAINT dishID FOREIGN KEY (idDish) REFERENCES dish (id),
  CONSTRAINT productiID FOREIGN KEY (idProduct) REFERENCES product (id)
);

-- ----------------------------
-- Table structure for order
-- ----------------------------
DROP TABLE IF EXISTS 'order';
CREATE TABLE 'order' (
id  INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
orderNumber  INTEGER NOT NULL DEFAULT 0,
date  TEXT NOT NULL,
total  REAL NOT NULL DEFAULT 0,
profit  real NOT NULL DEFAULT 0,
payed  INTEGER NOT NULL DEFAULT 1,
inversion real NOT NULL DEFAULT 0
);

-- ----------------------------
-- Table structure for orderDish
-- ----------------------------
DROP TABLE IF EXISTS orderDish;
CREATE TABLE orderDish (
  idOrder INTEGER NOT NULL,
  idDish INTEGER NOT NULL,
  price REAL DEFAULT 0,
  amount integer NOT NULL DEFAULT 0,
  PRIMARY KEY (idOrder, idDish),
  CONSTRAINT orderID FOREIGN KEY (idOrder) REFERENCES 'order' (id) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT dishID FOREIGN KEY (idDish) REFERENCES dish (id) ON DELETE NO ACTION ON UPDATE NO ACTION
);

-- ----------------------------
-- Table structure for product
-- ----------------------------
DROP TABLE IF EXISTS product;
CREATE TABLE product (
id  INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
productName  TEXT NOT NULL,
unitType  INTEGER NOT NULL,
price  REAL NOT NULL DEFAULT 0
);


-- ----------------------------
-- Table structure for storage
-- ----------------------------
DROP TABLE IF EXISTS storage;
CREATE TABLE storage (
  id INTEGER NOT NULL,
  amount REAL NOT NULL DEFAULT 0,
  PRIMARY KEY (id),
  CONSTRAINT productID FOREIGN KEY (id) REFERENCES product (id) ON DELETE NO ACTION ON UPDATE NO ACTION
);

-- ----------------------------
-- Table structure for storageTransaction
-- ----------------------------
DROP TABLE IF EXISTS storageTransaction;
CREATE TABLE storageTransaction (
  id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  type INTEGER NOT NULL,
  amount REAL NOT NULL DEFAULT 0,
  idProduct TEXT NOT NULL,
  date TEXT NOT NULL,
  idUser INTEGER NOT NULL,
  price REAL NOT NULL DEFAULT 0,
  CONSTRAINT productID FOREIGN KEY (idProduct) REFERENCES product (id) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT userID FOREIGN KEY (idUser) REFERENCES users (id) ON DELETE NO ACTION ON UPDATE NO ACTION
);

-- ----------------------------
-- Table structure for unit
-- ----------------------------
DROP TABLE IF EXISTS unit;
CREATE TABLE unit (
  id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  unit TEXT NOT NULL
);

-- ----------------------------
-- Table structure for users
-- ----------------------------
DROP TABLE IF EXISTS users;
CREATE TABLE users (
id  INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
user  TEXT NOT NULL,
password  TEXT NOT NULL,
name  TEXT NOT NULL,
role  INTEGER
);

-- ---------------------------------
-- Table structure for transactions
-- ---------------------------------
DROP TABLE IF EXISTS transactions;
CREATE TABLE transactions (
id  INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
type  INTEGER,
origin INTEGER,
amount  REAL DEFAULT 0,
idProduct  INTEGER,
date  TEXT,
idUser  INTEGER,
price  REAL,
merma  REAL,
aviable_in_local  REAL,
aviable_in_central  REAL,
productName TEXT,
unitType INTEGER,
suffix TEXT,
CONSTRAINT product FOREIGN KEY (idProduct) REFERENCES product (id),
CONSTRAINT user FOREIGN KEY (idUser) REFERENCES users (id)
);


INSERT INTO users VALUES (0, 'Invitado', '', 'Invitado', 1);
INSERT INTO users VALUES (1, 'admin', 'admin', 'Administrador', 0);