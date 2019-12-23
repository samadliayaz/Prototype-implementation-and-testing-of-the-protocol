# Prototype-implementation-and-testing-of-the-protocol
In a supervisory control and data acquisition (SCADA) system, there are field objects (e.g., controlled machines) and control objects (e.g., modules of the plant level control system). These objects have to exchange their data regularly: field objects send their status while the control objects send commands. This data exchange is provided by a protocol that includes the following phases:
 Establishing the connection: a link is built between a field and a control object.
 Object data transfer: each object sends its data to the other object in a regular manner.
The protocol uses the following messages:
 OBJ1 and OBJ2: Messages used in the phase of establishing the connection.
 OBJUP: Data transfer from the field object to the control object.
 OBJDOWN: Data transfer from the control object to the field object.
