# Fluent-UDF

UDF codes for ANSYS Fluent

**fsi_restricted.c** moves the interested boundary based on the recorded surface pressure to achieve FSI, where the solid part is simplified as a boundary. The geometry is a restricted vessel. The position of the nodes on the moving boundary is updated every 69 time steps.

**pulsatile_inlet.c** allows users to define the inlet profile. 
