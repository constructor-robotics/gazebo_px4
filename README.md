# gazebo_px4
ROS2 package for the usage of the gazebo simulation with the PX4 firmware







# adding DVL to model:
To Model:
         ```
         <sensor
              name="doppler_velocity_log"
              type="custom" gz:type="dvl">
            <pose degrees="true">0 0 -0.4 180 0 0</pose>
            <always_on>1</always_on>
            <update_rate>4</update_rate>
            <topic>/dvl/velocity</topic>
            <gz:dvl>
              <type>phased_array</type>
              <arrangement degrees="true">
                <beam id="1">
                  <aperture>2</aperture>
                  <rotation>45</rotation>
                  <tilt>30</tilt>
                </beam>
                <beam>
                  <aperture>2</aperture>
                  <rotation>135</rotation>
                  <tilt>30</tilt>
                </beam>
                <beam>
                  <aperture>2</aperture>
                  <rotation>-45</rotation>
                  <tilt>30</tilt>
                </beam>
                <beam>
                  <aperture>2</aperture>
                  <rotation>-135</rotation>
                  <tilt>30</tilt>
                </beam>
              </arrangement>
              <tracking>
                <bottom_mode>
                  <when>best</when>
                  <noise type="gaussian">
                    <!-- +/- 0.4 cm/s precision at 10 m/s within 2 stddevs -->
                    <stddev>0.002</stddev>
                  </noise>
                  <visualize>false</visualize>
                </bottom_mode>
              </tracking>
              <!-- Roughly 1 m resolution at a 100m -->
              <resolution>0.01</resolution>
              <maximum_range>100.</maximum_range>
              <minimum_range>0.1</minimum_range>
              <!-- ENU to SFM -->
              <reference_frame>0 0 0 0 0 0</reference_frame>
            </gz:dvl>
          </sensor>
          ```

to World:
`<plugin entity_name="*" entity_type="world" filename="gz-sim-dvl-system" name="gz::sim::systems::DopplerVelocityLogSystem"/>`
to server.config in gz_bridge
and comment out
`<plugin entity_name="*" entity_type="world" filename="libOpticalFlowSystem.so" name="custom::OpticalFlowSystem"/>`





