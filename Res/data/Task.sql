CREATE TABLE Task ( 
    uID             TEXT     PRIMARY KEY
                             NOT NULL
                             UNIQUE,
    TaskShortName   TEXT     NOT NULL,
    TaskState       INT      NOT NULL,
    TaskCreatedTime DATETIME NOT NULL,
    TaskCreatedDate DATE     NOT NULL,
    TaskStartTime   DATETIME,
    TaskStartDate   DATE,
    TaskDoneTime    DATETIME,
    TaskDoneDate    DATE,
    TaskConsumeTime INTEGER  NOT NULL,
    TaskComment     TEXT 
);
