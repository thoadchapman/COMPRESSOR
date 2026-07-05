import { useApp } from './AppContext';
import { useState } from 'react';
export default function StringCompressa() {
    const { compressa } = useApp();
    const [dicionario, setDicionario] = useState("");
    const [string, setString] = useState("");
    useEffect(() => {
        separador();
    }, [compressa]);

    const separador = () => {
        idx = compressa.indexOf("|");
        setDicionario(compressa.slice(0, idx));
        setString(compressa.slice(idx + 1));
    }
    const dictEntries = dicionario.split('');
    return (
        <div className='dicionario'>

        </div>
    );
}