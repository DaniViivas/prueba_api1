
// PROYECTO GRUPO #4 SASTRERIA







#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip> //SIRVE PARA USAR LA FUNCION SETW
using namespace std;


//------------------------------------------------------------------------------
// Variables de clientes
const int clientes = 10;
int indiceCliente;
string diaSemanaClientes[clientes] = {"Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo"};
string nombreClientes[clientes];
int edadClientes[clientes];
char generoClientes[clientes];
int cantidadClientes = 0;
int menuClientes;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int	opcionMenufacpag;	

struct DetalleFactura {
	/*double totalPagar = 0;*/
	string servicio;
	int cantidad;
	int puntos;
	double subtotal;
};
vector<DetalleFactura> detallesFactura;
vector<int> comprasPorProducto; // Vector para realizar un seguimiento de las compras por producto

//------------------------------------------------------------------------------

int opcionMenuPago;
//------------------------------------------------------------------------------
//Variables de pago Tarjeta
double montoTarjeta = 0.0;
// Variables de pago en efectivo
double cambioEfectivo = 0.0;
double efectivo = 0.0;
// Variables Transferencia
int bancoDestino;
double comision = 0.0;
double montoTransferencia =0.0;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//VariablesServicios
int puntos = 0;
int totalPuntosAcumulados=0;
struct servicio {
	string categoria;
	string nombre;
	double precio;
	string descuento;	
	int puntos;
};
int menuPrincipal;
int seleccionServicio;
const int numServicio = 8;
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
//FUNCION PARA PULSAR TECLA PARA AVANZAR
void esperarTecla() {
	cout << "Presiona Enter para continuar...";
	cin.ignore(); // Esto limpiará el buffer del teclado para que no afecte a futuras acciones
}
//------------------------------------------------------------------------------

servicio servicios[numServicio] = {
	{"ALQUILER             ", "Esmoquin 'Alta noche x día'", 1000.00, "De lunes a viernes 5% 2% fines de semana ", 30},
{"    ALQUILER         ", "Esmoquin para Boda x día   ", 800.000,  " De lunes a viernes 8%; 5% fines de semana", 20},
	{"CONFECCION           ", "Camisas                    ", 2500.00, "2da. camisa a mitad de precio            ", 15},
{"     CONFECCION      ", "Pantalones                 ", 2100.00, "Ninguno                                  ", 10},
	{"         CONFECCION  ", "Sacos                      ", 3000.00, "10% de descuento los fines de semana     ", 25},
{"MODIFICACION         ", "Zippers                    ", 100.000,  " Ninguno                                  ", 5},
	{"     MODIFICACION    ", "Pantalon                   ", 200.000,  " Ninguno                                  ", 5},
{"         MODIFICACION", "Camisas                    ", 250.000,  " Ninguno                                  ", 5},
};







//------------------------------------------------------------------------------
// Funciones de clientes
//Se utiliza una funcion para ingresar nuevo incliente y se llama con un switch
void ingresarCliente() {
	
	cout << "NUEVO CLIENTE" << endl;
	cout << "INGRESE SU NOMBRE: ";
	cin.ignore();
	getline(cin, nombreClientes[cantidadClientes]);
	cout << "INGRESE SU EDAD: ";
	cin >> edadClientes[cantidadClientes];
	
	bool generoValido = false;
	while (!generoValido) {
		cout << "INGRESE SU GÉNERO (M/F): ";
		cin >> generoClientes[cantidadClientes];
		
		if (generoClientes[cantidadClientes] == 'M' || generoClientes[cantidadClientes] == 'F' ||
			generoClientes[cantidadClientes] == 'm' || generoClientes[cantidadClientes] == 'f') {
			generoValido = true;
		} else {
			cout << "Género no válido. Debe ser 'M | m' (Masculino) o 'F | f' (Femenino)." << endl;
		}
	}
	
	cout << "+--------------------------+" << endl;
	cout << "+----- INGRESE EL DIA -----+" << endl;
	cout << "+--------------------------+" << endl;
	// Muestra la lista de días de la semana
	for (int i = 0; i  <7; i++) {
		cout << "| " << i  + 1 << ". " << diaSemanaClientes[i] << endl;
	}
	cout << "+--------------------------+" << endl;
	
	int opcionDia;
	cout << "Seleccione el número del día: ";
	cin >> opcionDia;
	
	while (opcionDia < 1 || opcionDia > 7) {
		cout << "Opción no válida. Ingrese un número de día válido: ";
		cin >> opcionDia;
	}
	
	// Asigna el día seleccionado al cliente
	diaSemanaClientes[cantidadClientes] = diaSemanaClientes[opcionDia - 1];
	
	cantidadClientes++;
}
//------------------------------------------------------------------------------





//------------------------------------------------------------------------------
// Funciones de clientes
//Se utiliza una funcion para bucar clientes y se llama buscarClientes() {
void buscarClientes() {
	int numeroListaABuscar;
	string nombreABuscar;
	int opcionBusqueda;
	int opcionElegida;
	vector<int> opcionesIndicesCoincidentes;
	
	cout << "Seleccione el método de búsqueda:" << endl;
	cout << "1. Buscar por nombre" << endl;
	cout << "2. Buscar por número de lista" << endl;
	cout << "Ingrese el número de la opción deseada: ";
	cin >> opcionBusqueda;
	
	if (opcionBusqueda == 1) {
		// Búsqueda por nombre
		cout << "Ingrese el nombre del cliente que desea buscar: ";
		cin.ignore();
		getline(cin, nombreABuscar);
		
		transform(nombreABuscar.begin(), nombreABuscar.end(), nombreABuscar.begin(), ::tolower);
		
		for (int i = 0; i < cantidadClientes; i++) {
			string nombreActual = nombreClientes[i];
			transform(nombreActual.begin(), nombreActual.end(), nombreActual.begin(), ::tolower);
			
			if (opcionBusqueda == 1 && nombreActual.find(nombreABuscar) != string::npos) {
				opcionesIndicesCoincidentes.push_back(i);
			}
		}
	} else if (opcionBusqueda == 2) {
		// Búsqueda por número de lista
		cout << "Ingrese el número de lista del cliente que desea buscar: ";
		
		while (true) {
			cin >> numeroListaABuscar;
			
			if (cin.fail()) {
				// Limpiar el estado del flujo de entrada y descartar caracteres no deseados
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Ingrese un número válido: ";
			} else {
				break;
			}
		}
		
		if (numeroListaABuscar < 1 || numeroListaABuscar > cantidadClientes) {
			cout << "Número de lista no válido." << endl;
			return;
		}
		
		// Agregar el índice correspondiente al número de lista buscado
		opcionesIndicesCoincidentes.push_back(numeroListaABuscar - 1);
	} else {
		cout << "Opción no válida." << endl;
		return;
	}
	
	// Realizar la búsqueda
	
	if (!opcionesIndicesCoincidentes.empty()) {
		cout << "Resultados de la búsqueda:" << endl;
		for (int i = 0; i < opcionesIndicesCoincidentes.size(); i++) {
			cout << i + 1 << ". " << nombreClientes[opcionesIndicesCoincidentes[i]] << endl;
		}
		
		cout << "Seleccione el número de la opción deseada: ";
		cin >> opcionElegida;
		if (opcionElegida >= 1 && opcionElegida <= opcionesIndicesCoincidentes.size()) {
			int indiceElegido = opcionesIndicesCoincidentes[opcionElegida - 1];
			cout << "Cliente encontrado:" << endl;
			cout << "Nombre: " << nombreClientes[indiceElegido] << endl;
			cout << "Edad: " << edadClientes[indiceElegido] << endl;
			cout << "Número de lista: " << indiceElegido + 1 << endl;
			cout << "Género: " << ((generoClientes[indiceElegido] == 'M' || generoClientes[indiceElegido] == 'm') ? "Masculino" : "Femenino") << endl;
		} else {
			cout << "Opción no válida." << endl;
		}
	} else {
		cout << "No se encontraron resultados para la búsqueda." << endl;
	}
	esperarTecla();
}

//------------------------------------------------------------------------------
// Funciones de clientes
//Se utiliza una funcion para mostar una lista de clientes ya ingresados y se llama con un switch
void mostrarClientes() {
	cout << "LISTA DE CLIENTES:" << endl;
	for (int i = 0; i < cantidadClientes; i++) {
		cout << "|---------------------------------------|"<<endl;
		cout << "Cliente " << i + 1 << ":" << endl;
		cout << "Nombre: " << nombreClientes[i] << endl;
		cout << "Edad: " << edadClientes[i] << endl;
		/*	cout << "Numero de lista: "<<cantidadClientes[i]<< endl;*/
		cout << "Género: " << ((generoClientes[i] == 'M' || generoClientes[i] == 'm') ? "Masculino" : "Femenino") << endl;
		cout << "Día de la Semana: " << diaSemanaClientes[i] << endl;
		cout << "|---------------------------------------|"<<endl;
	}
	esperarTecla();
}


//------------------------------------------------------------------------------
//verifica en cada compra si se selecciono un cliente, para no estar seleccionando en cada compra
int indiceClienteSeleccionado = -1;
bool clienteSeleccionado = false;
//------------------------------------------
int seleccionarCliente() {
	if (cantidadClientes == 0) {
		cout << "No hay clientes registrados. Por favor, ingrese un nuevo cliente." << endl;
		ingresarCliente();
		return cantidadClientes - 1;
	} else {
		mostrarClientes();
		cout << "Seleccione el número del cliente: ";
		cin >> indiceCliente;
		
		while (indiceCliente < 1 || indiceCliente > cantidadClientes) {
			cout << "Opción no válida. Ingrese un número de cliente válido: ";
			cin >> indiceCliente;
		}
		
		return indiceCliente - 1;
	}
}
//------------------------------------------------------------------------------


void realizarCompra(int indiceCliente) {
	int seleccionServicio = -1;
	
	// Inicializar el vector de compras por producto con ceros
	comprasPorProducto.resize(numServicio, 0);
	
	do {
		
		
		if (indiceClienteSeleccionado == -1) {
			indiceClienteSeleccionado = seleccionarCliente();
		}
		system("cls");
		cout << " | ------------------------------------------------------------------------------------------------------------------------------- | " << endl;
		cout << " | Producto                  | Modelo                            | Precio     | Descuentos                                | Puntos | " << endl;
		cout << " | ------------------------------------------------------------------------------------------------------------------------------- | " << endl;
		
		for (int i = 0; i < numServicio; i++) {
			cout << " | " << servicios[i].categoria << "     | " << i + 1 << ". " << servicios[i].nombre
				<< "    | L. " << servicios[i].precio << "    | " << (servicios[i].descuento ) << " | " << servicios[i].puntos << "     | " << endl;
		}
		cout << " |                           | 0. Salir al menu principal | " <<endl;
		cout << " | ---------------------------------------------------------------------------------------------------------------------------------------- | " << endl;
		
		int seleccionServicio, cantidadDias;
		cout << "Ingrese el número del servicio que desea comprar: ";
		cin >> seleccionServicio;
		
		if (seleccionServicio == 0) {
			break; // Salir del bucle si la selección es 0
		}
		
		if (seleccionServicio == 1 || seleccionServicio == 2) {
			cout << "Ingrese la cantidad de días para el alquiler: ";
			cin >> cantidadDias;
			
			
			if (cantidadDias <= 0) {
				cout << "La cantidad de días debe ser mayor que cero." << endl;
				return;
			}
		}
		
		// Actualizar el seguimiento de compras por producto
		if (seleccionServicio >= 1 && seleccionServicio <= numServicio) {
			servicio servicioSeleccionado = servicios[seleccionServicio - 1];
			comprasPorProducto[seleccionServicio - 1]++; // Incrementar la cantidad de clientes que compraron este producto
			
			// Aplicar la lógica para calcular el precio total basado en la cantidad de días
			double precioTotal;
			
			if (seleccionServicio == 1 || seleccionServicio == 2) {
				precioTotal = servicioSeleccionado.precio * cantidadDias;
			} else {
				precioTotal = servicioSeleccionado.precio;
			}
			
			DetalleFactura detalle;
			
			detalle.servicio = servicioSeleccionado.nombre;
			detalle.cantidad = (seleccionServicio == 1 || seleccionServicio == 2) ? cantidadDias : 1;
			detalle.puntos = servicioSeleccionado.puntos;
			detalle.subtotal = precioTotal;
			detallesFactura.push_back(detalle);
			cout << "Puntos acumulados en esta compra: " << servicioSeleccionado.puntos << endl;
			totalPuntosAcumulados += servicioSeleccionado.puntos;		
			cout << "Puntos acumulados en total: " << totalPuntosAcumulados << endl;
			cout << "Compra realizada con éxito. Total a pagar: L. " << precioTotal << endl;
			cout << " Cualquier descuento se aplicara en la factura... " << endl;
			
			//Añadir el if de si se quiere seguir comprando
			
			char seguirComprando;
			cout << "¿Desea seguir comprando? (S/N): ";
			cin >> seguirComprando;
			
			// Validar que la respuesta sea 'S', 's', 'N', o 'n'
			while (seguirComprando != 'S' && seguirComprando != 's' && seguirComprando != 'N' && seguirComprando != 'n') {
				cout << "Opción no válida. Por favor, ingrese 'S' o 'N': ";
				cin >> seguirComprando;
			}
			
			if (seguirComprando != 'S' && seguirComprando != 's') {
				break; // Salir del bucle si no se desea seguir comprando
			}
			
			
			
		} else {
			cout << "Número de servicio no válido." << endl;
		}
		esperarTecla();
	} while (true);
}


void mostrarInventario() {
	cout << " | -------------------------------------------------------------------------------------------------------------------------------------- | " << endl;
	cout << " |                                                  D E T A L L E S   D E   F A C T U R A                                                 | " << endl;
	cout << " |                                                S A S T R E R I A   P U M A   G A L A N T                                               | " << endl;
	cout << " | -------------------------------------------------------------------------------------------------------------------------------------- | " << endl;
	cout << " | Producto                       | Modelo                    | Precio               | Descuentos                                | Puntos | " << endl;
	cout << " | ------------------------------ |---------------------------|----------------------|------------------------------------------ |------- | " << endl;
	cout << " | ALQUILER                       | Esmoquin 'Alta noche'     | L. 1000.00 x día     | De lunes a viernes 5%, 2% fines de semana | 30     | " << endl;
	cout << " |                                                                                   | 'Cargo adicional de: L.200 por demora'    |        | " << endl;
	cout << " |         ALQUILER               | Esmoquin para Boda        | L. 800.00 x día      | De lunes a viernes 8%, 5% fines de semana | 20     | " << endl;
	cout << " |                                                                                   | 'Cargo adicional de: L.300 por demora'    |        | " << endl;
	cout << " | -------------------------------------------------------------------------------------------------------------------------------------- | " << endl;
	cout << " | CONFECCION                     | Camisas                   | L. 2,500.00          | 2da. camisa a mitad de precio             | 15     | " << endl;
	cout << " |          CONFECCION            | Pantalones                | L. 2,100.00          | Ninguno                                   | 10     | " << endl;
	cout << " |                   CONFECCION   | Sacos                     | L. 3,000.00          | 10% de descuento los fines de semana      | 25     | " << endl;
	cout << " | -------------------------------------------------------------------------------------------------------------------------------------- | " << endl;
	cout << " | MODIFICACION                   | Zippers                   | L. 100.00            | Ninguno                                   | 5      | " << endl;
	cout << " |       MODIFICACION             | Pantalon                  | L. 200.00            | Ninguno                                   | 5      | " << endl;
	cout << " |             MODIFICACION       | Camisas                   | L. 250.00            | Ninguno                                   | 5      | " << endl;
	cout << " | -------------------------------------------------------------------------------------------------------------------------------------- | " << endl;
	esperarTecla();
}
char respTrajeEA = ' '; 
char respTrajeEB = ' ';
double verFactura(int indiceCliente) {
	if (indiceClienteSeleccionado == -1) {
		indiceClienteSeleccionado = seleccionarCliente();
	}
	system("cls");
	
	double totalPagar = 0.0;
	//--------------------------------------------------------------------------
	//Logica para cargo Adicionales
	//Logica para Esmoquin Alta Noche
	//--------------------------------------------------------------------------

	double cargoEsmoquinA = 200;
	for (const auto& detalle : detallesFactura) {
		if (detalle.servicio == "Esmoquin 'Alta noche x día'") {
			while (respTrajeEA == ' ') { // Bucle hasta que se proporcione una respuesta válida
				cout << " | ¿Se entregó el traje Esmoquin 'Alta noche' a tiempo? S / N | " << endl;
				cin >> respTrajeEA;
				// Validar que la respuesta sea 'S', 's', 'N', o 'n'
				if (respTrajeEA != 'S' && respTrajeEA != 's' && respTrajeEA != 'N' && respTrajeEA != 'n') {
					cout << " | Opción no válida. Por favor, ingrese 'S' o 'N' | " << endl;
					respTrajeEA = ' '; // Reiniciar la variable para volver a preguntar
				}
			}
		}
	}
	
	//Logica para Esmoquin Boda
	double cargoEsmoquinB = 300;
	for (const auto& detalle : detallesFactura) {
		if (detalle.servicio == "Esmoquin para Boda x día   ") {
			while (respTrajeEB == ' ') { // Bucle hasta que se proporcione una respuesta válida
				cout << " | ¿Se entregó el traje Esmoquin 'Boda' a tiempo? S / N | " << endl;
				cin >> respTrajeEB;
				// Validar que la respuesta sea 'S', 's', 'N', o 'n'
				if (respTrajeEB != 'S' && respTrajeEB != 's' && respTrajeEB != 'N' && respTrajeEB != 'n') {
					cout << " | Opción no válida. Por favor, ingrese 'S' o 'N' | " << endl;
					respTrajeEB = ' '; // Reiniciar la variable para volver a preguntar
				}
			}
		}
	}
	//--------------------------------------------------------------------------
	system("cls");
	cout << " | ------------------------------------------------------------------------------------------------------------------------------- | " << endl;
	cout << " | ------------------------------------------------------------------------------------------------------------------------------- | " << endl;
	cout << " | Datos Cliente | " << endl;
	cout << " | ------------------------------------------------------------------------------------------------------------------------------- | " << endl;
	cout << " | Nombre: " << nombreClientes[indiceCliente] << endl;
	cout << " | Edad: " << edadClientes[indiceCliente] << endl;
	
	cout << " | Género: " << ((generoClientes[indiceCliente] == 'm' || generoClientes[indiceCliente] == 'M') ? "Masculino" : "Femenino") << endl;
	cout << " | Dia: " << diaSemanaClientes[indiceCliente] << endl;
	/*    cout << " | Numero de lista: " << cantidadClientes[indiceCliente] << endl;*/
	cout << " | ------------------------------------------------------------------------------------------------------------------------------- | " << endl;
	cout << " | Servicio                  | Cantidad | Puntos  | Subtotal           | " << endl;
	cout << " | ------------------------------------------------------------------------------------------------------------------------------- | " << endl;
	for (const auto& detalle : detallesFactura) {
		cout << " | " << setw(27) << left << detalle.servicio << " | " << setw(8) << detalle.cantidad << " | " << setw(7) << detalle.puntos << " | L. " << setw(18) << fixed << setprecision(2) << detalle.subtotal << " | " << endl;
	}
	cout << " | ------------------------------------------------------------------------------------------------------------------------------- | " << endl;
	cout << " | ------------------------------------------------------------------------------------------------------------------------------- | " << endl;
	// Logica Descuentos
	

	double descuento60edad = 0.0;
	double descuento3raedad = 0.10;
	
	// Calcular el total antes de descuentos e impuestos
	for (const auto& detalle : detallesFactura) {
		totalPagar += detalle.subtotal;
	}
	
	
	
	//Descuento Esmoquin AltaNoche
	double descuento5diaEA=0.05;
	double descuento2finSemanaEA=0.02;
	for (const auto& detalle : detallesFactura) {
		if (detalle.servicio == "Esmoquin 'Alta noche x día'") { //se cololoca el nombre de la variable que se necesita encontrar 
			
			if (diaSemanaClientes[indiceCliente] == "Lunes" || diaSemanaClientes[indiceCliente] == "Martes" || diaSemanaClientes[indiceCliente] == "Miércoles" || diaSemanaClientes[indiceCliente] == "Jueves" || diaSemanaClientes[indiceCliente] == "Viernes") {
				cout << " | ------------------------------------------------------------------------------------------------------------------------------- | " << endl;
				cout << " | Descuento del 5% aplicado para 'Esmoquin Alta Noche' de lunes a viernes: L. " << (descuento5diaEA * detalle.subtotal) << endl;
				totalPagar = totalPagar - descuento5diaEA * detalle.subtotal;
			} 
			if (diaSemanaClientes[indiceCliente] == "Sabado" || diaSemanaClientes[indiceCliente] == "Domingo") {
				cout << " | ------------------------------------------------------------------------------------------------------------------------------- | " << endl;
				cout << " | Descuento del 2% aplicado para 'Esmoquin Alta Noche' los fines de semana: L. " << (descuento2finSemanaEA * detalle.subtotal) << endl;
				totalPagar = totalPagar - descuento2finSemanaEA * detalle.subtotal;
			}
		}
	}	
	
	//Descuento Esmoquin Boda
	double descuento5diaEB=0.08;
	double descuento2finSemanaEB=0.05;
	for (const auto& detalle : detallesFactura) {
		if (detalle.servicio == "Esmoquin para Boda x día   ") { //se cololoca el nombre de la variable que se necesita encontrar 
			
			if (diaSemanaClientes[indiceCliente] == "Lunes" || diaSemanaClientes[indiceCliente] == "Martes" || diaSemanaClientes[indiceCliente] == "Miércoles" || diaSemanaClientes[indiceCliente] == "Jueves" || diaSemanaClientes[indiceCliente] == "Viernes") {
				cout << " | ------------------------------------------------------------------------------------------------------------------------------- | " << endl;
				cout << " | Descuento del 8% aplicado para 'Esmoquin para Boda' de lunes a viernes: L. " << (descuento5diaEB * detalle.subtotal) << endl;
				totalPagar = totalPagar - descuento5diaEB * detalle.subtotal;
			} 
			if (diaSemanaClientes[indiceCliente] == "Sabado" || diaSemanaClientes[indiceCliente] == "Domingo") {
				cout << " | ------------------------------------------------------------------------------------------------------------------------------- | " << endl;
				cout << " | Descuento del 5% aplicado para 'Esmoquin para Boda los fines de semana: L. " << (descuento2finSemanaEB * detalle.subtotal) << endl;
				totalPagar = totalPagar - descuento2finSemanaEB * detalle.subtotal;
			}
		}
	}
	
	//Descuento Confeccion de Sacos
	double descuento2finSemanaSaco=0.10;
	for (const auto& detalle : detallesFactura) {
		if (detalle.servicio == "Sacos                      ") { //se cololoca el nombre de la variable que se necesita encontrar, tal y como se escribio en la estructura unu
			
			if (diaSemanaClientes[indiceCliente] == "Sabado" || diaSemanaClientes[indiceCliente] == "Domingo") {
				cout << " | ------------------------------------------------------------------------------------------------------------------------------- | " << endl;
				cout << " | Descuento del 5% aplicado para 'Confeccion de Sacos' los fines de semana: L. " << (descuento2finSemanaSaco * detalle.subtotal) << endl;
				totalPagar = totalPagar - descuento2finSemanaSaco * detalle.subtotal;
			}
		}
	}
	//--------------------------------------------------------------------------
	//CargosAdicionales
	//Cargo Esmoquin Alta Noche
	if (respTrajeEA == 'N' || respTrajeEA == 'n') {
		totalPagar = totalPagar + cargoEsmoquinA;
		cout << " | ------------------------------------------------------------------------------------------------------------------------------- | " << endl;
		cout << " | Cargo por demora en Esmoquin 'Alta noche' de 200 Lempiras | " << endl;
		
	}
	else if (respTrajeEA == 'S' || respTrajeEA == 's') {
		cout << " | ------------------------------------------------------------------------------------------------------------------------------- | " << endl;
		cout << " | Se entregó el traje a tiempo, no hay cargo por demora | " << endl;
	}
	
	//--------------------------------------------------------------------------
	//CargosAdicionales
	//Cargo Esmoquin Alta Noche
	if (respTrajeEB == 'N' || respTrajeEB == 'n') {
		totalPagar = totalPagar + cargoEsmoquinB;
		cout << " | ------------------------------------------------------------------------------------------------------------------------------- | " << endl;
		cout << " | Cargo por demora en Esmoquin 'Boda' de 300 Lempiras | " << endl;
		
	}
	else if (respTrajeEB == 'S' || respTrajeEB == 's') {
		cout << " | ------------------------------------------------------------------------------------------------------------------------------- | " << endl;
		cout << " | Se entregó el traje a tiempo, no hay cargo por demora | " << endl;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	// Calcular descuento para personas de 60 años en adelante
	if (edadClientes[indiceCliente] >= 60) {
		descuento60edad = totalPagar * descuento3raedad;
		
		totalPagar -= descuento60edad;
	}
	
	
	// Calcular  impuesto general del 15%
	double impuestoGeneral = 0.15;
	double totalConIsv = totalPagar * impuestoGeneral;
	
	/*	cout << "Impuesto del 15% aplicado: L. " << totalConIsv << endl;*/
	totalPagar += totalConIsv;
	
	
	if (descuento60edad>0) {
		cout << " | ------------------------------------------------------------------------------------------------------------------------------- | " << endl;
		cout << " | Descuento del 10% aplicado para clientes de 60 años en adelante: L. " << descuento60edad << endl;
	}
	cout << " | ------------------------------------------------------------------------------------------------------------------------------- | " << endl;
	cout << " | Impuesto Sobre Ventas: L" << totalConIsv << endl;
	cout << " | ------------------------------------------------------------------------------------------------------------------------------- | " << endl;
	cout << " | Total Puntos Acumulados: " << totalPuntosAcumulados << endl;
	cout << " | ------------------------------------------------------------------------------------------------------------------------------- | " << endl;
	cout << " | Total a pagar: L. " << setw(62) << fixed << setprecision(2) << totalPagar << endl;
	cout << " | ------------------------------------------------------------------------------------------------------------------------------- | " << endl;
	
	
	esperarTecla();
	//detallesFactura.clear();  // Limpiar detalles después de mostrar la factura
	return totalPagar; // Devolver el total a paga
	
	
}
//------------------------------------------------------------------------------




// Función para realizar el pago en efectivo
void pagoEfectivo() {
	
	double totalPagar = verFactura(indiceClienteSeleccionado);
	if (totalPagar>=1) {
		
		
		const double tasaCambio = 0.041; // Supongamos que 1 lempira = 0.041 dólares
		
		double totalPagarLempiras = verFactura(indiceClienteSeleccionado);
		double totalPagarDolares = totalPagarLempiras * tasaCambio;
		
		
		system("cls");
		
		
		
		
		system("cls");
		while (efectivo < totalPagarDolares) {
			cout << "|--------------------------------------------|" << endl;
			cout << "|-----     Ha seleccionado efectivo     -----|" << endl;
			cout << "| Usted debe:  $ " << totalPagarDolares << " (dólares)   |" << endl;
			cout << "|--------------------------------------------|" << endl;
			cout << "| Ingrese el monto a pagar: $ ---------------|" << endl;
			cout << "|--------------------------------------------|" << endl;
			cin >> efectivo;
			
			if (efectivo < totalPagarDolares) {
				//Funcion para limpiar pantalla 
				system("cls");
				cout << "|---------------------------------------------------|" << endl;
				cout << "|----- La cantidad ingresada es menor al total -----|" << endl;
				cout << "|---------------------------------------------------|" << endl;
				
			}
		}	
		
		esperarTecla();
		if (efectivo >= totalPagarDolares) {
			efectivo /23;
			cout << "|--------------------------------------------|" << endl;
			cout << "| Total pagado: $ " << efectivo << " dólares|" << endl;
			cout << "|--------------------------------------------|" << endl;
			cambioEfectivo = efectivo - totalPagarDolares;
			if (cambioEfectivo >= 0) {
				
				cout << "|---------------------------------------------------------------|" << endl;
				cout << "|----- Su cambio es de: $ " << cambioEfectivo << " dólares -----|" << endl;
				cout << "|---------------------------------------------------------------|" << endl;
			} else {
				cout << "|---------------------------------------------|" << endl;
				cout << "|----- Cambio restante: $ 0.00 (dólares) -----|" << endl;
				cout << "|---------------------------------------------|" << endl;
			}
			
			
			
			cout << "|--------------------------------------------|" << endl;
			cout << "| Total pagado: $ " << totalPagarDolares << " dólares |" << endl;
			cout << "|--------------------------------------------|" << endl;
			cout << "|              CodRecibo:123145              |" << endl;
			cout << "|              Fecha:07/12/2023              |" << endl;
			cout << "|                 Hora:00:19                 |" << endl;
			cout << "|  Direccion: Tegucigalpa, Barrio La Ronda   |" << endl;
			cout << "|--------------------------------------------|" << endl;
			cout << "|--------------------------------------------|" << endl;
			cout << "|-----      Sastretia 'Puma Galant'     -----|" << endl;
			cout << "|--------------------------------------------|" << endl;
			
			
			// Restablecer variables después de realizar el pago
			respTrajeEA = ' ';
			respTrajeEB = ' ';
			totalPuntosAcumulados= 0.0;
			efectivo = 0.0;
			cambioEfectivo = 0.0;
			detallesFactura.clear();
		}
		
		esperarTecla();
	}else {
		
		system("cls");
		cout << " Aun no se han realizado compras " <<endl;
		system("pause");
		
	}
	
}

//Funcion Pago Tarjeta
void pagoTarjeta() {
	
	
	double totalPagar = verFactura(indiceClienteSeleccionado);
	if (totalPagar>=1) { 
		
		
		system("cls");
		
		
		while (montoTarjeta<totalPagar||montoTarjeta>totalPagar) {
			// Pago con tarjeta
			system("cls");
			cout << "|-------------------------------------------|" << endl;
			cout << "|-----     Ha seleccionado Tarjeta     -----|" << endl;
			cout << "|-- Usted debe:             $ " << totalPagar << " Lempiras --|" << endl;
			cout << "|-------------------------------------------|" << endl;
			cout << "|-----        VISA /  MASTER CARD      -----|" << endl;
			cout << "|-------------------------------------------|" << endl;
			cout << "|  Ingrese el monto a pagar con tarjeta: $  |" << endl;
			cout << "|-------------------------------------------|" << endl;
			cin >> montoTarjeta;
			
			
			if(montoTarjeta<totalPagar) {
				system("cls");
				cout << "|---------------------------------------------------|" << endl;
				cout << "|--- El monto pagado con tarjeta es insuficiente ---|" << endl;
				cout << "|---------------------------------------------------|" << endl;
				//Funcion para continuar solo si tocamos una tecla
				esperarTecla();
			} 
			if (montoTarjeta>totalPagar)  {
				system("cls");
				cout << "|-----------------------------------------------|" << endl;
				cout << "|  El monto pagado con tarjeta debe ser exacto  |" << endl;
				cout << "|-----------------------------------------------|" << endl;
				//Funcion para continuar solo si tocamos una tecla
				esperarTecla();
			}
			if (montoTarjeta== totalPagar) {
				system("cls");
				cout << "|-------------------------------------------|" << endl;
				cout << "|-- Pago con tarjeta realizado con exito  --|" << endl;
				cout << "|-------------------------------------------|" << endl;
				cout << "| Total pagado con tarjeta: $. " << montoTarjeta << " Lempiras|" << endl;
				cout << "|-------------------------------------------|" << endl;
				cout << "|-----     Sastreria 'Puma Galant'     -----|" << endl;
				cout << "|-------------------------------------------|" << endl;
				cout << "|-------------------------------------------|" << endl;
				cout << "|-----     Ha seleccionado Tarjeta     -----|" << endl;
				cout << "|-----       Credito/Debito VISA       -----|" << endl;
				cout << "|-------------------------------------------|" << endl;
				cout << "|        |4000 - 1234 - 5353- 2432|         |" << endl;
				cout << "|-------------------------------------------|" << endl;
				cout << "|          |Venc: 12/26|     |***|          |" << endl;
				cout << "|-------------------------------------------|" << endl;
				cout << "|              CodRecibo:123145             |" << endl;
				cout << "|              Fecha:07/12/2023             |" << endl;
				cout << "|                 Hora:00:19                |" << endl;
				cout << "|  Direccion: Tegucigalpa, Barrio La Ronda  |" << endl;
				cout << "|-------------------------------------------|" << endl;
				//Funcion para continuar solo si tocamos una tecla
			}
			esperarTecla();		
			
			
			// Restablecer variables después de realizar el pago
			respTrajeEA = ' ';
			respTrajeEB = ' ';
			totalPuntosAcumulados= 0.0;
			efectivo = 0.0;
			cambioEfectivo = 0.0;
			detallesFactura.clear();
			
			
		}
		esperarTecla();	
		
	}else {
		
		system("cls");
		cout << " Aun no se han realizado compras " <<endl;
		system("pause");
		
	}
	
	
}


// Función para realizar el pago por transferencia
void pagoTransferencia() {
	
	double totalPagar = verFactura(indiceClienteSeleccionado); 
	if (totalPagar>=1) {
		
		
		
		double totalTransferencia = montoTransferencia + comision;
		
		system("cls");
		do {
			cout << "|-------------------------------------------------|" << endl;
			cout << "|-----     Ha seleccionado Transferencia     -----|" << endl;
			cout << "|--    Usted debe: $ " << totalPagar << " Lempiras    --|" << endl;
			cout << "|-------------------------------------------------|" << endl;
			cout << "|  Ingrese el monto a transferir: $ ";
			cin >> montoTransferencia;
			
			if (montoTransferencia != totalPagar) {
				// Mostrar mensaje de monto incorrecto
				cout << "| El monto ingresado no es igual al total. Intente de nuevo. |" << endl;
				system("pause");
				system("cls");
			}
		} while (montoTransferencia != totalPagar);
		
		cout << "Seleccione el banco destino: " << endl;
		cout << "1. BAC" << endl;
		cout << "2. Atlantida" << endl;
		cout << "3. Ficohsa" << endl;
		cout << "4. Otro (CARGO DE UN 3% ADICIONAL)" << endl;
		cin >> bancoDestino;
		
		if (bancoDestino == 1 || bancoDestino == 2 || bancoDestino == 3 || bancoDestino == 4) {
			system("cls");
			cout << "|-------------------------------------------------|" << endl;
			cout << "|-- Pago por transferencia realizado con exito  --|" << endl;
			cout << "|-------------------------------------------------|" << endl;
			
			double comision = 0.0;
			
			if (bancoDestino == 4) {
				// Se cobra el 3% de comisión para bancos diferentes
				comision = montoTransferencia * 0.03;
				montoTransferencia += comision;
				cout << "| Comision por transferencia: $. " << comision << " Lempiras|" << endl;
			}
			
			cout << "| Total pagado por transferencia: $. " << montoTransferencia << " Lempiras|" << endl;
			cout << "|-------------------------------------------------|" << endl;
			cout << "|-----        Sastreria 'Puma Galant'        -----|" << endl;
			cout << "|-------------------------------------------------|" << endl;
			cout << "|                |4000123453532432|               |" << endl;
			cout << "|-------------------------------------------------|" << endl;
			cout << "|                 CodRecibo:123145                |" << endl;
			cout << "|                 Fecha:07/12/2023                |" << endl;
			cout << "|                    Hora:00:19                   |" << endl;
			cout << "|     Direccion: Tegucigalpa, Barrio La Ronda     |" << endl;
			cout << "|-------------------------------------------------|" << endl;
			
			
			// Restablecer variables después de realizar el pago
			respTrajeEA = ' ';
			respTrajeEB = ' ';
			totalPuntosAcumulados= 0.0;
			efectivo = 0.0;
			cambioEfectivo = 0.0;
			detallesFactura.clear();
			
		}
		
		cout << "Presiona Enter para continuar...";
		system("pause");
		
	}else {
		
		system("cls");
		cout << " Aun no se han realizado compras " <<endl;
		system("pause");
		
	}
	
	
}

// Función para imprimir el informe por producto/servicio
void imprimirInforme() {
	cout << " _____________________________________________\n";
	cout << "\n|  Informe de compras por producto/servicio:  |\n";
	cout << " ---------------------------------------------\n";
	cout << endl;
	cout << "________________________________________\n";
	
	for (int i = 0; i < numServicio; i++) {
		cout << "Producto/Servicio: " << servicios[i].nombre << "\n";
		cout << "Cantidad de producto adquirido: " << comprasPorProducto[i] << "\n";
		cout << "----------------------------------------\n";
		cout << endl;
	}
}





int main(int argc, char *argv[]) {
	
	
	cout<<" | ------------------------------------------- | " <<endl;
	cout<<" | -----          BIENVENIDOS A          ----- | " <<endl;
	cout<<" | -----          LA SASTRERIA           ----- | " <<endl;
	cout<<" | -----           PUMA GALANT           ----- | " <<endl;
	cout<<" | ------------------------------------------- | " <<endl;
	esperarTecla();
	
	do {
		
		
		system("cls");
		cout << " | ------------------------------------------- | " << endl;
		cout << " | -----         MENU PRINCIPAL          ----- | " << endl;
		cout << " | -----            SASTRERIA            ----- | " << endl;
		cout << " | -----           PUMA  GALAN           ----- | " << endl;	
		cout << " | ------------------------------------------- | " << endl;
		cout << " | -----  1. MENU DE CLIENTES            ----- | " << endl;
		cout << " | -----  2. MENU DE COMPRAS             ----- | " << endl;
		cout << " | -----  3. INVENTARIO Y OBSERVACIONES  ----- | " << endl;
		cout << " | -----  4. REPORTES                    ----- | " << endl;
		cout << " | -----  5. FACTURAR Y PAGAR            ----- | " << endl;
		cout << " | -----  0. SALIR                       ----- | " << endl;
		cout << " | ------------------------------------------- | " << endl;
		cin >> menuPrincipal;
		
		
		switch (menuPrincipal) { 
			
		case 1:
			system("cls");
			
			while (true) {
				//Funcion para limpiar pantalla 
				system("cls");
				
				cout << " | ---------------------------------- | " << endl;
				cout << " | -----      MENU CLIENTES     ----- | " << endl;
				cout << " | ---------------------------------- | " << endl;
				cout << " | -----  1. INGRESAR CLIENTES  ----- | " << endl;
				cout << " | -----  2. BUSCAR   CLIENTES  ----- | " << endl;
				cout << " | -----  3. MOSTRAR  CLIENTES  ----- | " << endl;
				cout << " | -----  4. MENU     PRINCIPAL ----- | " << endl;
				cout << " | ---------------------------------- | " << endl;
				cin >> menuClientes;
				
				switch (menuClientes) {
				case 1:
					//Funcion para limpiar pantalla 
					system("cls");
					//Funcion para llamar a ingresar cliene
					ingresarCliente();
					//Funcion para continuar solo si tocamos una tecla
					std::cout << "Presiona Enter para continuar...";
					esperarTecla();
					break;
					
				case 2:
					//Funcion para limpiar pantalla 
					system("cls");
					//Funcion para llamar a buscar clientes//Funcion para continuar solo si tocamos una tecla
					buscarClientes();
					//Funcion para continuar solo si tocamos una tecla
					std::cout << "Presiona Enter para continuar...";
					esperarTecla();
					break;
					
				case 3:
					//Funcion para limpiar pantalla 
					system("cls");
					//Funcion para llamar a mostrar clientes
					mostrarClientes();
					//Funcion para continuar solo si tocamos una tecla
					std::cout << "Presiona Enter para continuar...";
					esperarTecla();
					break;
					
				case 4:
					break;
					
				default:
					cout << "Opción no válida." << endl;
					esperarTecla();
					break;
				}
				
				if (menuClientes == 4) {
					break;
				}
			}
			
			
			break;
		case 2:
			system("cls");
			// Selecciona un cliente antes de comprar solo si no se ha realizado antes
			indiceClienteSeleccionado = -1;
			
			realizarCompra(indiceClienteSeleccionado);
			esperarTecla();
			break;
		case 3:
			system("cls");
			mostrarInventario();
			esperarTecla();
			break;
		case 4:
			//REPORTER
			system("cls");
			
			while (true){
				
				int opcionReportes=0;
				system("cls");
				cout << " | ---------------------------------- | " << endl;
				cout << " | -----      MENU REPORTES     ----- | " << endl;
				cout << " | ---------------------------------- | " << endl;
				cout << " | -----  1. VER REPORTES       ----- | " << endl;
				cout << " | -----  2. GENERAR DOCUMENTO  ----- | " << endl;
				cout << " | -----  3. MENU PRINCIPAL     ----- | " << endl;
				cout << " | ---------------------------------- | " << endl;
				cout << "\n Ingrese una opcion: "<<endl;
				cin >> opcionReportes;
				
				esperarTecla();
				system("cls");
				
				switch (opcionReportes) {
				case 1:
					imprimirInforme();
					esperarTecla();
					system("cls");
					break;
				case 2:
					while (true){
						system("cls");
						
						//Almacenar elementos en un archivo.
						cout << " | ----------------------------------- | " << endl;
						cout << " | -- Almacenando en un archivo ... -- | " << endl;
						cout << " | ----------------------------------- | " << endl;
						cout << " "<<endl;
						esperarTecla();
						
						ofstream archivo("Reportes de compras.txt");
						
						archivo << "Estos son los reportes de compras de cada producto/servicio:" << endl;
						archivo << "     "<<endl;
						
						
						for (int i = 0; i < numServicio; i++) {
							archivo << "Producto/Servicio: " << servicios[i].nombre << "\n";
							archivo << "Cantidad de producto adquirido: " << comprasPorProducto[i] << "\n";
							archivo << "----------------------------------------\n";
							archivo << endl;
						}
						
						system("cls");
						cout << " | ------------------------------------------- | " << endl;
						cout << " | -- Elementos almacenados en el archivo:  -- | " << endl;
						cout << " | --        Reportes de compras.txt        -- | " << endl;
						cout << " | --                                       -- | " << endl;
						cout << " | -- En la carpeta de descargas...         -- | " << endl;
						cout << " | ------------------------------------------- | " << endl;
						cout << " "<<endl;
						
						esperarTecla();
						archivo.close();
						
						break;
					}
					break;	
				case 3:
					system("cls");
					cout << "REGRESANDO AL MENU PRINCIPAL..."<<endl;
					break;
				default:
					cout << "Opción no válida." << endl;
					esperarTecla();
					break;	
				}
				
				if (opcionReportes == 3) {
					break;
				}
			}
			
			esperarTecla();
			break;
			
		case 5:
			
			
			
			while (true) {
				
				system("cls");
				cout << " | ---------------------------------------- | " << endl;
				cout << " | ----- Seleccione la opcion deseada ----- | " << endl;
				cout << " | ----- 1.FACTURA                    ----- | " << endl;
				cout << " | ----- 2.PAGAR                      ----- | " << endl;
				cout << " | ----- 0.SALIR                      ----- | " << endl;
				cout << " | ---------------------------------------- | " << endl;
				cin >>opcionMenufacpag;
				
				switch (opcionMenufacpag){
					
					
				case 1:
					verFactura(indiceClienteSeleccionado);
					esperarTecla();
					break;
				case 0:
					system("cls");
					cout << "REGRESANDO AL MENU PRINCIPAL..."<<endl;
					esperarTecla();
					break;
				default:
					cout << "Opción no válida." << endl;
					esperarTecla();
					break;
				case 2:
					double totalPagar = verFactura(indiceClienteSeleccionado);
					system("cls");
					cout << "| El total a pagar es de: " <<totalPagar <<endl;
					do {
						system("cls");
						cout << " | ---------------------------------------------- | " << endl;
						cout << " | Seleccione el método de pago de su preferencia | " << endl;
						cout << " | ---------------------------------------------- | " << endl;
						cout << " | -----             MENU DE PAGO           ----- | " << endl;
						cout << " | ---------------------------------------------- | " << endl;
						cout << " | -----  1. EFECTIVO                       ----- | " << endl;
						cout << " | -----  2. TARJETA (CREDITO/DEBITO)       ----- | " << endl;
						cout << " | -----  3. TRANSFERENCIA                  ----- | " << endl;
						cout << " | -----  0. SALIR                          ----- | " << endl;
						cout << " | ---------------------------------------------- | " << endl;
						
						cin >> opcionMenuPago;
						
						switch (opcionMenuPago) {
						case 1:
							
							pagoEfectivo();
							break;
							
						case 2:
							
							pagoTarjeta();
							break;
							
						case 3:
							
							pagoTransferencia();
							break;
							
						case 0:
							cout << "SALIENDO..." << endl;
							break;
							
						default:
							cout << "Opción no válida. Intente de nuevo." << endl;
						}
						
					} while (opcionMenuPago != 0);
					esperarTecla();
					break;
					
				}//Llave switch
				
				if (opcionMenufacpag == 0) {
					break;
				}
			} 
			//Final Case5
			esperarTecla();
			break;
			
		case 0:
			system("cls");
			cout << "SALIENDO..."<<endl;
			esperarTecla();
			break;
			
		default:
			cout << "Opción no válida." << endl;
			//Funcion para continuar solo si tocamos una tecla
			
			esperarTecla();
			break;
			
		}
		
		
		
		
		
		
	} while (menuPrincipal != 0);
	return 0;
}
