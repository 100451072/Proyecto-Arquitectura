Normas de cálidad del código

El código fuente debe estar bien estructurado y organizado, así como apropiadamente documentado.
Se recomienda, pero no es de obligado cumplimiento, hacer uso de las C++ Core Guidelines (http:
//isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines).
En cualquier caso, las siguientes reglas si son de obligado y estricto cumplimiento:
No se podrán utilizar variables globales que no sean constantes.
No está permitido el uso del patrón Singleton.
No se podrá pasar arrays a una función como parámetros de tipo puntero.
Ninguna función ni función miembro podrá tener más de cuatro parámetros.
Ninguna función podrá tener más de 25 líneas estando apropiadamente formateadas.
Todos los parámetros se pasarán a las funciones por valor, por referencia o por referencia cons-
tante.
No se podrá usar explicitamente las funciones malloc() o free() ni los operadores new o delete.
No se permite el uso de macros, excepto para la definición de guardas de inclusión.
No se permite ningún cast excepto static_cast, dynamic_cast, const_cast o reinterpret_cast.


Advertencias:

Si el código entregado no compila, la nota final de la práctica será de 0.
Si se ignora injustificadamente alguna norma de calidad de código, la nota final de la práctica
será de 0.
En caso de copia todos los grupos implicados obtendrán una nota de 0. Además se notificará a
la dirección de la EPS para la correspondiente apertura de expediente disciplinario.