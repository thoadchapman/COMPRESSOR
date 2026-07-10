import { useComp } from './useComp';
import { useApp } from './AppContext';

type InputArquivoProps = {
    setArquivo: (file: File | null) => void;
};

export default function InputArquivo({ setArquivo }: InputArquivoProps) {
    const { setOriginal } = useApp();
    const comp = useComp();

    const handleFileChange = (e: React.ChangeEvent<HTMLInputElement>) => {
        const file = e.target.files?.[0];
        if (!file) return;

        setArquivo(file);
        setOriginal(file);

        const reader = new FileReader();
        reader.onload = async (event) => {
            const arrayBuffer = event.target?.result;
            if (!arrayBuffer) return;

            const uint8Array = new Uint8Array(arrayBuffer as ArrayBuffer);
            const base64 = btoa(String.fromCharCode(...uint8Array));
            await comp('COMPRIMIR', base64);
        };
        reader.readAsArrayBuffer(file);
    };

    return (
        <div className="input-container">
            <input
                type="file"
                placeholder="escolha para comprimir..."
                onChange={handleFileChange}
                className="custom-input"
            />
        </div>
    );
}