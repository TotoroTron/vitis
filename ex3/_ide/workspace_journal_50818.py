# 2025-11-03T15:39:45.977526
import vitis

client = vitis.create_client()
client.set_workspace(path="ex3")

comp = client.create_hls_component(name = "dct",cfg_file = ["hls_config.cfg"],template = "empty_hls_component")

comp = client.get_component(name="dct")
comp.run(operation="C_SIMULATION")

comp.run(operation="SYNTHESIS")

vitis.dispose()

