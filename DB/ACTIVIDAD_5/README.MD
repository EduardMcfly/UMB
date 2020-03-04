# ACTIVITY 5 SQL Basic Scripts

## Steps

1. On master

   stop server on master,

   set server-id = 1,

   enable log-bin=mysql-bin in my.ini, start mysql server

2. On slave

   stop mysql server,

   set server-id =2 in my.ini

   start mysql server

3. On master create replication user on master with slave IP like below

   ```sql
   CREATE USER 'repli_user'@'slave_IP' IDENTIFIED BY 'password';

   GRANT REPLICATION SLAVE ON *.* TO 'repli_user'@'slave_IP';
   ```

4. Go To Master

   flush tables with read lock;

   show master status;
   (note offset file number and offset position)

   unlock tables;

5. On slave

   ```sql
   CHANGE MASTER TO
   master_host = 'master_IP',
   master_user = 'repli_user',
   master_password= 'password',
   master_log_file = 'mysql-bin.<file-number>',
   master_log_pos = offset-pos;
   ```

6. On slave

   ```sql
   start slave;
   show slave status;
   ```

   You should get "Waiting for master to send event" as slave status;
