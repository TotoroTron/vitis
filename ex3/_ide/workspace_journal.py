# 2025-11-07T15:25:03.074755
import vitis

client = vitis.create_client()
client.set_workspace(path="ex3")

comp = client.get_component(name="dct")
comp.run(operation="SYNTHESIS")

comp.run(operation="C_SIMULATION")

comp.run(operation="SYNTHESIS")

vitis.dispose()

