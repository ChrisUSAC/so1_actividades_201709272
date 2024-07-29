#!/bin/bash

# Definir la variable GITHUB_USER
GITHUB_USER="ChrisUSAC"

# Consultar la API de GitHub
response=$(curl -s "https://api.github.com/users/$GITHUB_USER")

# Extraer información del JSON de la respuesta
# Se necesita tener instalado jq para poder ejecutar este script
# Para instalar jq en Ubuntu: sudo apt-get install jq
id=$(echo "$response" | jq -r '.id')
created_at=$(echo "$response" | jq -r '.created_at')

# Verificar si se obtuvieron resultados válidos
if [ "$id" = "null" ] || [ "$created_at" = "null" ]; then
  echo "Error al consultar la API de GitHub, por favor verifica el nombre de usuario."
  exit 1
fi

# Imprimir el mensaje
message="Hola $GITHUB_USER. User ID: $id. Cuenta fue creada el: $created_at."
echo "$message"

# Crear el archivo de log
log_date=$(date +"%Y-%m-%d")
log_dir="/tmp/$log_date"
# Crear el directorio si no existe
mkdir -p "$log_dir"
# Crear el archivo de log
log_file="$log_dir/saludos.log"

# Escribir el mensaje en el archivo de log, sobreescribiendo el contenido
echo "$message" > "$log_file"

# Añadir el cronjob para ejecutar el script cada 5 minutos
(crontab -l 2>/dev/null; echo "*/5 * * * * $(realpath $0)") | crontab -

# Cómo eliminar el cronjob
# Para eliminar este cronjob, sigue estos pasos:
# 1. Abre el crontab en modo de edición con el comando: crontab -e
# 2. Busca la línea que contiene el cronjob añadido por este script:
#    */5 * * * * /ruta/completa/al/script/github_user_info.sh
# 3. Elimina esa línea o coméntala añadiendo un '#' al inicio.
# 4. Guarda y cierra el editor (en Nano, esto se hace presionando Ctrl+X, luego Y y Enter).