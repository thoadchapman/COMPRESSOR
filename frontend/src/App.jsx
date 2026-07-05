import { useState } from 'react';
import { useApp } from './AppContext';
import { useCompDescomp } from './compDescomp';
import './App.css';

function App() {
    const [texto, setTexto] = useState('');
    const { comprimido } = useApp();
    const compDescomp = useCompDescomp();

    const handlePress = async (e) => {
        if (e.key === 'Enter') {
            e.preventDefault();
            if (texto?.trim()) {
                await compDescomp(true, texto);
            }
        }
    };

    return (
        <div className='porra-toda'>
            <title>compressor.</title>
            <body>
                <h1>compressor.</h1>
                <input
                    type="text"
                    placeholder="digite"
                    value={texto}
                    onChange={e => setTexto(e.target.value)}
                    onKeyDown={handlePress}
                />
                {comprimido && <p>Resultado: {comprimido}</p>}
            </body>
        </div>
    );
}

export default App;