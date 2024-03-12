import subprocess
import json
###################################################################################################################################
###################################################################################################################################
def analizar_archivo_c(archivo, comando):
    salida_archivo = f"{archivo}.out.txt"
    errores_archivo = f"{archivo}.err.txt"
    comando = ["frama-c","-pdg", "-pdg-dot", "graph", "-pdg-print"] + comando.split() + ["-cpp-extra-args=-I ext_include/", archivo]
    with open(salida_archivo, "w") as salida, open(errores_archivo, "w") as errores:
        proceso = subprocess.Popen(comando, stdout=salida, stderr=errores)
        salida_proceso, errores_proceso = proceso.communicate()
    
    if proceso.returncode == 0:
        print(f"Análisis exitoso para el archivo: {archivo}")
    else:
        print(f"Error al analizar el archivo: {archivo}")
        print("Verifica el archivo de errores para más detalles:", errores_archivo)
###################################################################################################################################
###################################################################################################################################

def dot_to_json(archivo):
    salida_archivo = f"{archivo}_to_json.out.txt"
    errores_archivo = f"{archivo}_to_json.err.txt"
    nombre_archivo_entrada = f"graph.__sys_{archivo}.dot"
    nombre_archivo_salida = f"graph.{archivo}.json"
    comando = ["dot", "-Txdot_json", nombre_archivo_entrada]
    with open(nombre_archivo_salida, "w") as salida:
        proceso = subprocess.Popen(comando, stdout=subprocess.PIPE)
        stdout, stderr = proceso.communicate()
        salida.write(stdout.decode("utf-8"))
                                     
    if proceso.returncode == 0:
        print(f"Dot to json exitoso para la syscall: {archivo}")
    else:
        print(f"Error al analizar la syscall: {archivo}")
        print("Verifica el archivo de errores para más detalles:", errores_archivo)
    return nombre_archivo_salida
###################################################################################################################################
###################################################################################################################################

def analyze_dependencies(names):
    dependencies = []
    for name in names:
        # Analyze dependencies
        with open(name, 'r') as file:
            data = json.load(file)

            for edge in data['objects']:
                if 'label' in edge and edge['label'].startswith("In("):
                    dependencies.append({name.split(".")[1]: edge['label']})
    with open("implicit-dependencies.json", "w") as out_file:
        json.dump(dependencies, out_file, indent=4)





###################################################################################################################################
###################################################################################################################################
def generate_output_file(name):
        # Cargar el JSON de entrada
    with open(name, 'r') as f:
        data = json.load(f)

    # Diccionario para almacenar las dependencias
    dependencies = {}

    # Recorrer cada objeto en el JSON
    for obj in data:
        for key, value in obj.items():
            # Obtener el nombre y la condición
            name = key
            condition = value
            
            # Buscar otras coincidencias en el resto del JSON
            for other_obj in data:
                for other_key, other_value in other_obj.items():
                    other_name = other_key
                    other_condition = other_value
                    
                    # Verificar si la condición coincide y no es el mismo objeto
                    if condition == other_condition and name != other_name:
                        # Almacenar la dependencia
                        if name not in dependencies:
                            dependencies[name] = [other_name]
                        else:
                            dependencies[name].append(other_name)

    # Crear el JSON de salida
    output_data = []
    for name, deps in dependencies.items():
        output_data.append({
            name: {"dependencies": deps}
        })

    # Guardar el JSON de salida
    with open('implicit-dep-output.json', 'w') as f:
        json.dump(output_data, f, indent=4)

###################################################################################################################################
###################################################################################################################################

def main():
    archivos_comandos = {
        "seti_1/seti_1.c": " -main __sys_seti_1",
        "seti_2/seti_2.c": " -main __sys_seti_2",
        "seti_3/seti_3.c": " -main __sys_seti_3"
    }
    syscalls = {
        "seti_1", "seti_2", "seti_3"
    }
    
    archivos_json = [
        "graph.seti_1.json", "graph.seti_2.json", "graph.seti_3.json"
    ]

    for archivo, comando in archivos_comandos.items():
        analizar_archivo_c(archivo, comando)
    
    for syscall in syscalls:
        name = dot_to_json(syscall)
 
    analyze_dependencies(archivos_json)
    
    generate_output_file("implicit-dependencies.json")


if __name__ == "__main__":
    main()


