Proyecto de Refactorización

Code Smells

•	Instanciación múltiples: La clase Inventario podría ser instanciada varias veces si se declara como un miembro en varias clases o si se usa el constructor libremente. Se pueden usar métodos especiales como setUp() para preparar datos o estados comunes antes de cada prueba.

•	Alto Acoplamiento: Las clases de cliente (como main o comandos) tenían que interactuar con muchos subsistemas (Inventario, Ventas, Clientes) y conocer sus métodos internos y el ciclo de vida de los datos.

•	Violación del OCP (Lógica de Instanciación): Si la clase SistemaTienda creara directamente los informes, necesitaría modificar su código cada vez que se agregara un nuevo tipo de informe.

•	Métodos Ligeramente Largos (Lógica de Menú): Las funciones menuGerente y menuEmpleado contienen grandes bloques de switch/case con toda la lógica de cada acción, haciendo difícil la adición de nuevas opciones.

•	Código Duplicado (Formato de Tabla): Las funciones de Inventario(mostrarProductos, buscarProductoPorBusqueda, buscarPorDescripcion) repetían la misma lógica para mostrar el encabezado de la tabla de productos.

•	Código duplicado (lógica de cálculo): En la clase ReporteAnual, la lógica de cálculo y filtrado de datos por mes se duplicaba entre el método generar() y escribirContenidoArchivo().

•	Método Largo (ReporteMensual::generar()): El método generar() en que ReporteMensual contiene la lógica de filtrar, calcular el resumen estadístico y mostrar el top de productos.



Patrones Aplicados
Patrón Singleton (Inventario)
Se aplico este patrón a la clase Inventario para asegurar que solo exista una única instancia de inventario en toda la aplicación.
Implementación: Se hizo el constructor de Inventario privado y proporcionamos un método estático público ( getInstance()) para que cualquier otra parte del sistema pueda acceder a esa única instancia compartida de productos.

Patrón Comando (Opciones de Menú)
Se utilizo el patrón Comando para convertir cada opción o acción del menú (como "Agregar Producto" o "Realizar Venta") en una clase de objeto independiente .
Implementación: Se creo una interfaz base Comando con el método ejecutar(). Luego, se creo comandos concretos (ej. ComandoAgregarProducto, ComandoRealizarVenta) que encapsulan la lógica de la acción y la referencia al objeto que la ejecuta (el Receiver , que es la instancia de SistemaTienda).

Patrón Fachada (SistemaTienda)
Se convirtio la clase SistemaTienda en una Fachada para simplificar el acceso a las funcionalidades complejas del sistema (como Ventas y Clientes).
Implementación: La clase SistemaTienda exponen métodos simples y de alto nivel (ej. realizarVenta) que internamente coordinan varias acciones en los subsistemas complejos (ej. buscar cliente, validar inventario, obtener siguiente ID de venta, guardar la venta).

Patron Fabrica (ReporteFactory)
Se implementó la clase ReporteFactory con el método estático crearReporte() para manejar la creación de objetos de la familia Reporte( ReporteMensual, ReporteAnual).
Implementación: La clase ReporteFactory centraliza la lógica de instanciación y decide qué objeto concreto retornar. Esto permite que el código cliente (SistemaTienda::menuReportes) sea independiente de las clases concretas.



Se realizaron tres factorizaciones principales para mejorar la cohesión, reducir la duplicación y hacer el código más limpio y manejable.
1. Factorización de la Lógica Estadística de Reportes Mensuales
Problema Corregido: El método ReporteMensual::generar()era demasiado largo y manejaba varias responsabilidades a la vez.
Refactorización: Se creó el nuevo método mostrarResumenEstadistico().
Justificación: Se logró repartir la responsabilidad en dos funciones, no solo en una. Cada método ahora es simple , se enfoca en una sola cosa y las funcionalidades están separadas, resultando en mejor orden y coherencia..

2. Factorización del Formato de Tabla en Inventario
Problema Corregido: Existía duplicación de código en al menos tres funciones de Inventario(mostrarProductos, mostrarProductoPorBusqueda, buscarPorDescripcion) que repetían exactamente el mismo formato para el encabezado de la tabla de productos.
Refactorización: Se agregó la función Inventario::mostrarEncabezadoTabla().
Justificación: Al centralizar el formato de la tabla en una sola función, se eliminó la duplicación de datos innecesarios, se separó la responsabilidad y se obtuvo un código más limpio.

3. Factorización de Cálculo de Datos Anuales
Problema Corregido: Las funciones ReporteAnual::generar() y ReporteAnual::escribirContenidoArchivo()duplicaban la lógica de negocio (cálculos de totales y filtros por mes).
Refactorización: Se creó el método que retorna una estructura ReporteAnual::calcularDatosAnuales() DatosAnuales.
Justificación: Se centralizó la lógica de negocio en una única función. Ahora se obtienen todos los datos calculados una sola vez , haciendo que las demás funciones ya no necesiten recalcular (evitando el bucle duplicado) y haciendo el código más limpio y eficiente..




Conclusión
El desarrollo del proyecto nos ayudó a aplicar en la práctica varios patrones de diseño para mejorar cómo está organizado el sistema de tienda y hacerlo más fácil de mantener y ampliar. Al revisar el código identificamos varios code smells, como duplicación de funciones, métodos muy largos, demasiado acoplamiento entre clases y casos donde el código no seguía principios como OCP. Gracias a esto pudimos corregirlos usando patrones como Singleton, Comando, Fachada y Fábrica, que nos permitieron simplificar el sistema, separar mejor las responsabilidades y dejar listo el proyecto para crecer sin complicaciones.
En resumen, este proyecto combinó análisis y práctica real, mostrando la importancia de crear software modular, ordenado y fácil de extender. La experiencia demuestra que aplicar patrones de diseño y hacer refactorización no solo mejora el código actual, sino que también deja todo más preparado para futuros cambios sin perder calidad.
