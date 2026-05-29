ML Source Code:
import tensorflow as tf
import numpy as np
X = np.array([[0.1],[0.2],[0.15],[0.9],[1.0],[0.85]])
y = np.array([0,0,0,1,1,1])
model = tf.keras.Sequential([
    tf.keras.layers.Dense(8, activation='relu', input_shape=(1,)),
    tf.keras.layers.Dense(1, activation='sigmoid')
])
model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])
model.fit(X, y, epochs=100)
model.save("model.h5")
