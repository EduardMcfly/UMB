# ACTIVIDAD 5 Scripts básicos SQL

## Pasos

1. En master

   Detener el servidor en el maestro,

   Establecer id del servidor = 1,

   Habilite log-bin = mysql-bin en my.ini, inicie el servidor mysql

2. En esclavo

   Detener el servidor mysql,

   Establecer server-id = 2 en my.ini

   Iniciar servidor mysql

3. En el maestro, cree un usuario de replicación en el maestro con IP esclava como se muestra a continuación

   ```sql
   CREATE USER 'repli_user'@'slave_IP' IDENTIFIED BY 'password';

   GRANT REPLICATION SLAVE ON *.* TO 'repli_user'@'slave_IP';
   ```

4. Ir al maestro

   ```sql
   flush tables with read lock;

   show master status;
   # nota número de archivo de desplazamiento y posición de desplazamiento

   unlock tables;
   ```

5. En esclavo

   ```sql
   CHANGE MASTER TO
   master_host = 'master_IP',
   master_user = 'repli_user',
   master_password= 'password',
   master_log_file = 'mysql-bin.<file-number>',
   master_log_pos = offset-pos;
   ```

6. En esclavo

   ```sql
   start slave;
   show slave status;
   ```

   Debería obtener "Esperando a que el maestro envíe el evento" como estado esclavo;
